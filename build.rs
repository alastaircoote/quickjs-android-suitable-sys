use std::env;
use std::path::PathBuf;

fn main() {
    build_library();
    generate_bindings();
}

fn build_library() {
    let base_dir = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap());
    let code_dir = base_dir.join("quickjs");

    let quickjs_version =
        std::fs::read_to_string(code_dir.join("VERSION")).expect("failed to read quickjs version");

    let mut builder = cc::Build::new();

    #[cfg(feature = "dump_leaks")]
    builder.define("DUMP_LEAKS", None);

    #[cfg(feature = "bignum")]
    builder.define("CONFIG_BIGNUM", None);

    builder
        .files(
            [
                "cutils.c",
                "libbf.c",
                "libregexp.c",
                "libunicode.c",
                "quickjs.c",
            ]
            .iter()
            .map(|f| code_dir.join(f)),
        )
        .file(base_dir.join("quickjs+extern.c"))
        .define("_GNU_SOURCE", None)
        .define(
            "CONFIG_VERSION",
            format!("\"{}\"", quickjs_version.trim()).as_str(),
        )
        // The below flags are used by the official Makefile.
        .flag("-Wchar-subscripts")
        .flag("-Wno-array-bounds")
        .flag_if_supported("-Wno-format-truncation")
        .flag("-Wno-missing-field-initializers")
        .flag("-Wno-sign-compare")
        .flag("-Wno-unused-parameter")
        .flag("-Wundef")
        .flag("-Wuninitialized")
        .flag("-Wunused")
        .flag("-Wwrite-strings")
        .flag("-funsigned-char")
        // Below flags are added to supress warnings that appear on some
        // platforms.
        .flag_if_supported("-Wno-cast-function-type")
        .flag("-Wno-implicit-fallthrough")
        // cc uses the OPT_LEVEL env var by default, but we hardcode it to -O2
        // since release builds use -O3 which might be problematic for quickjs,
        // and debug builds only happen once anyway so the optimization slowdown
        // is fine.
        .opt_level(2)
        .compile("quickjs");
}

fn generate_bindings() {
    // Turns out QuickJS bindings look really different when you're building for
    // Android i686. Why? No idea! But bindgen doesn't check platform, so we have to manually
    // specify it.
    let target = env::var("TARGET").expect("Could not read the target platform");

    let header_path =
        PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap()).join("quickjs+extern.h");
    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());

    // Generate bindings.
    let bindings = bindgen::Builder::default()
        .header(
            header_path
                .to_str()
                .expect("Could not create QuickJS path")
                .to_string(),
        )
        .clang_arg(format!("--target={}", target))
        // When in Android i686 JSValue becomes an f64. So we force JSValue to be
        // opaque in all other situations, so we don't try to read out tags
        // or anything like that and suddenly discover things break on i686.
        // .opaque_type("JSValue")
        .whitelist_function("JS.*")
        .whitelist_type("JS.*")
        .whitelist_var("JS.*")
        .size_t_is_usize(true)
        .generate()
        .expect("Unable to generate bindings");

    // Write the bindings to the $OUT_DIR/bindings.rs file.
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings!");
}
