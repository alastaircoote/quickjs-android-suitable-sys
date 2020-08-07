# quickjs-android-suitable-sys

FFI Bindings for [quickjs](https://bellard.org/quickjs/). One of [many](https://crates.io/search?q=quickjs), but I created this one as a fork of [libquickjs-sys](https://crates.io/crates/libquickjs-sys) becuse it wasn't working properly on i686 Android.

## What?

The i686 toolchain is used when building for the Android emulator and more or less nothing else these days. It turns out that [bindgen](https://github.com/rust-lang/rust-bindgen) isn't aware of compilation target by default and for some reason the code generated for 64bit OSes will crash on i686 Android (and maybe others). This crate rebuilds the bindings whenever the library is built, ensuring platform consistency.

Making this change breaks compatibility with the higher level library used by libquickjs-sys, so I made a fresh fork. There are a bunch of required functions (e.g. `JS_NewBool`) inlined in the header file rather than in the `.c` file, so the C compiler doesn't include them. To that end I've created `quickjs+extern.c` to expose those functions correctly.

## Extra features

- `bignum`
  
  Enable this to add bigint support to QuickJS

- `dump_leaks`

  Dumps out variables still being held in the JS engine whenever it is released. Useful to debugging memory leaks.