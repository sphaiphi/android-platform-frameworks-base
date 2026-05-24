# Plan: NDK Upgrade and Bundle/Intent Refactoring

## Phase 1: Environment Upgrade and Documentation [checkpoint: 73b04e3]
Upgrade the project toolchain to NDK r29 and update architectural documentation to reflect the move to `std::expected`.

- [x] Task: Update `conductor/tech-stack.md` to NDK r29 and `std::expected`. 92ca390
- [x] Task: Update build configuration (e.g., `CMakeLists.txt`) to target NDK r29 toolchain. 9ae16a0
- [x] Task: Verify toolchain upgrade by building the current project (ignoring deprecation warnings for now).
- [x] Task: Conductor - User Manual Verification 'Phase 1: Environment Upgrade and Documentation' (Protocol in workflow.md) 73b04e3

## Phase 2: Refactor Bundle to use std::expected
Migrate the `Bundle` implementation from `std::optional` to `std::expected`.

- [x] Task: Update `Bundle.h` signatures to use `std::expected`. 11542d7
- [x] Task: Refactor `Bundle.cpp` implementation to return `std::expected`. 4d0cee5
- [x] Task: Update `Bundle_test.cpp` and `Bundle_cts_test.cpp` to handle `std::expected` results. 25146d2
- [x] Task: Verify `Bundle` build and test pass.
- [ ] Task: Conductor - User Manual Verification 'Phase 2: Refactor Bundle to use std::expected' (Protocol in workflow.md)

## Phase 3: Refactor Intent to use std::expected [checkpoint: 14104c6]
Migrate the `Intent` implementation from `std::optional` to `std::expected`, ensuring compatibility with the updated `Bundle`.

- [x] Task: Update `Intent.h` signatures to use `std::expected`. c81baf5
- [x] Task: Refactor `Intent.cpp` implementation. 5eddd0a
- [x] Task: Update `Intent_test.cpp` and `Intent_cts_test.cpp`. fa326f6
- [x] Task: Verify `Intent` build and test pass.
- [x] Task: Conductor - User Manual Verification 'Phase 3: Refactor Intent to use std::expected' (Protocol in workflow.md) 14104c6

## Phase 4: Structural Refactoring and Test Organization [checkpoint: 70a4975]
Reorganize directory structure/namespaces and enhance the test suite.

- [x] Task: Apply namespace/directory structure changes to `core/cpp/android/os` and `core/cpp/android/content`. 99e7d27
- [x] Task: Update CMake includes and source paths to reflect structural changes. 12ba37f
- [x] Task: Reorganize and expand unit tests for better coverage of edge cases. 712cca7
- [x] Task: Final verification of all tests (Core and CTS). 12ba37f
- [x] Task: Conductor - User Manual Verification 'Phase 4: Structural Refactoring and Test Organization' (Protocol in workflow.md) 70a4975
