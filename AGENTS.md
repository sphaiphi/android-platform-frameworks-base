# AGENTS.md: Android Framework Core

This project is the core of the Android framework, containing the source code for fundamental components of the Android operating system.

## Project Overview

C++23 re-implementation of core Android framework components (Intent, Bundle, Activity, View, Resources, etc.) for NDK developers. Java sources in `core/java/` serve as the functional reference baseline.

**Branch:** `lineageos-23.0` (track); `main` for PRs.

**Key Technologies:**

*   **C++:** The primary language for the Android framework development, using modern C++ standards (C++23).
*   **Java:** Sources are included for reference to guide the C++ implementation.
*   **AIDL (Android Interface Definition Language):** Used for defining the programming interface that both client and service agree upon in order to communicate with each other using interprocess communication (IPC).
*   **CMAKE:** The build system used for compiling the C++ code for host and testing.
*   **NDK:** Android Native Development Kit for on-device builds.

**Architecture:**

The Android framework is a layered architecture. The C++ implementation provides the core functionality, with Java sources as references. The files are organized in the `core/cpp` directory, focusing on the C++ API framework layer.

## Building and Running

All C++ code is C++23. Two parallel build systems:

```bash
# Host development build (CMake + GoogleTest)
cmake -B build -S core/cpp
cmake --build build

# Run unit tests
cd build && ctest --output-on-failure

# Run single test
cd build && ctest -R Intent_test --output-on-failure
# Or: ./tests/framework_tests --gtest_filter="IntentTest.*"

# CTS tests (separate build directory)
cmake -B build_cts -S cts/cpp/tests
cmake --build build_cts
cd build_cts && ./framework_cts_tests

# Android on-device build (ndk-build)
cd core/cpp && ndk-build
```

The host build defines `HOST_BUILD` and uses mock binder headers from `include/android_mock/`.

## Code Layout

```
core/cpp/
├── include/android/        # Public headers (75+ files)
├── src/android/            # Implementations (44+ .cpp files)
├── src/android_mock/       # Mock binder for host builds
├── aidl/android/           # Generated AIDL C++ bindings
├── specs/android/          # AIDL spec files
├── tests/                  # 54 unit test files (GoogleTest)
├── CMakeLists.txt          # Main library: android_framework_core (static .a)
└── Android.mk              # NDK shared library build

core/java/                  # AOSP Java sources — reference only, not built
cts/                        # Compatibility Test Suite
├── cpp/tests/              # C++ CTS tests (GoogleTest)
└── java/tests/             # Java reference tests from AOSP CTS
conductor/                  # Project management (plans, specs, workflow)
```

## Development Conventions

The codebase follows strict coding conventions and a well-defined structure.

*   **Namespace Structure:** All C++ code mirrors Android SDK packages: `android::app`, `android::content`, `android::view`, `android::widget`, `android::os`, `android::graphics`, `android::util`, `android::content::res`.
*   **Licensing:** The code is licensed under the Apache License, Version 2.0, as indicated in the file headers.
*   **Documentation:** The code is documented with comments suitable for C++ documentation tools.
*   **Testing:** The Android project has a comprehensive testing strategy, including unit tests, integration tests, and compatibility tests (CTS) for the C++ components.

## Key Documentation

- **`core/cpp/CPP.md`** — C++23 coding standard (safety dimensions, design patterns, auto-reject rules)
- **`cts/xUNIT.md`** — GoogleTest testing methodology and assertion philosophy
- **`conductor/workflow.md`** — TDD workflow: spec → failing test → implementation → CTS validation
- **`conductor/product.md`** — Product vision and functional priorities
- **`conductor/tech-stack.md`** — C++23, AIDL, NDK r29, GoogleTest, CMake

## Development Workflow

1. Tasks are tracked in `conductor/tracks/` plan files
2. Write failing tests first (Red phase)
3. Implement minimum code to pass (Green phase)
4. Refactor while tests pass
5. Commit code, then update plan with commit SHA
6. For spec-driven tasks: spec in `core/cpp/specs/` → unit tests → CTS validation

No automated linting. Code quality is enforced via strict compiler flags (`-Wall -Wextra -Werror -Wpedantic`) and the documented safety-first coding standards in `CPP.md`.

This `AGENTS.md` file provides a high-level overview of the Android framework project developed in modern C++. Given the size and complexity of the codebase, this analysis is just a starting point for further exploration.
