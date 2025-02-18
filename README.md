# nlohmann-json-example

The code samples for using [nlohmann/json](https://github.com/nlohmann/json) in C++ projects.

- [Documentation](https://nlohmann.github.io/json/)
- [/docs/examples](https://github.com/nlohmann/json/tree/develop/docs/examples)

## About nlohmann/json 

### 基本的な特徴

- C++11以降に対応
- ヘッダーオンリー
- STLコンテナとの自然な相互運用が可能
- only support UTF-8 encoding
- memory usage, speed は最優先ではない (RapidJSON, simdjson の方が速い)

### 注意すべき点

1. エラーハンドリング
   - パース時のエラーは例外として通知される
   - 適切な例外処理の実装が必要
2. カスタム型の対応
   - 独自の型を使用する場合は、to_json/from_json関数の実装が必要
   - ADLの仕組みを理解して実装する必要がある

## C++ Json Library alternatives

- [nativejson-benchmark](https://github.com/miloyip/nativejson-benchmark#parsing-time)
- [rapidjson](https://github.com/Tencent/rapidjson/)
- [simdjson](https://github.com/simdjson/simdjson)

## About this template

A template for C++ projects using CMake.
This repository includes settings for the following tools:

- [CMake](https://cmake.org/)
- [Google Test](https://github.com/google/googletest)
- [clang-format](https://clang.llvm.org/docs/ClangFormat.html)
- [clang-tidy](https://clang.llvm.org/extra/clang-tidy/)
- [VSCode](https://code.visualstudio.com/)
  - [clangd (VSCode Extension)](https://clangd.llvm.org/)
  - [CMake Tools (VSCode Extension)](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
  - [C/C++ Include Guard (VSCode Extension)](https://marketplace.visualstudio.com/items?itemName=akiramiyakoda.cppincludeguard)

## Directoris

The directory structure is based on [The Pitchfork Layout (PFL)](https://api.csswg.org/bikeshed/?force=1&url=https://raw.githubusercontent.com/vector-of-bool/pitchfork/develop/data/spec.bs).
(but there are some differences.)

- `include/` : Contains public header files for users.
- `src/` : Contains source files (including private header files and cmake scripts).
- `test/` : Contains test files.
- `examples/` : Contains example files.
- `external/` : Contains source files and libraries from external projects.
- `data/` : Contains not explicitly code files.
- `tool/` : Contains scripts and tools.
  - `cmake/` : Contains CMake scripts.
- `doc/` : Contains documents.

The following directories are not included in the repository, but these names are reserved.

- `build/` : Temporary build directory.
- `install/` : Temporary install directory.

If you want to add submodule projects, you need to add the following directories.

- `lib/` : the root directory of the submodule projects.
- `extra/` : the root directory of the submodule projects with some dependencies.
