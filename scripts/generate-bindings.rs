// cargo-deps: bindgen="0.55.1"

use std::env;
use std::path::PathBuf;

extern crate bindgen;

fn generate_bindings() {
    // Turns out QuickJS bindings look really different when you're building for
    // Android i686. Why? No idea! But bindgen doesn't check platform, so we have to manually
    // specify it.
    // let target = env::var("TARGET").expect("Could not read the target platform");

    let header_path =
        PathBuf::from(env::var("CARGO_SCRIPT_BASE_PATH").unwrap()).join("../quickjs+extern.h");
    let out_path = PathBuf::from(env::var("CARGO_SCRIPT_BASE_PATH").unwrap()).join("../src");

    // Generate bindings.
    let bindings = bindgen::Builder::default()
        .header(
            header_path
                .to_str()
                .expect("Could not create QuickJS path")
                .to_string(),
        )
        
        // .clang_arg(format!("--target={}", target))
        // When in Android i686 JSValue becomes an f64. So we force JSValue to be
        // opaque in all other situations, so we don't try to read out tags
        // or anything like that and suddenly discover things break on i686.
        .opaque_type("JSValue")
        .whitelist_function("(JS|js).*")
        .whitelist_type("(JS|js).*")
        .whitelist_var("(JS|js).*")
        .size_t_is_usize(true)
        .derive_debug(true)
        .generate()
        .expect("Unable to generate bindings");

    // Write the bindings to the $OUT_DIR/bindings.rs file.
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings!");
}

fn main() {
    generate_bindings();
}
