# Technology Stack

## Core Framework (Native)
*   **Primary Language:** Modern C++ (Standard: C++23)
*   **Safety Standards:** C++ Core Guidelines, Safety-First Idioms (Type, Bounds, Lifetime, Init, Error).
*   **Build System:** `ndk-build` (utilizing `Android.mk` scripts for system-level integration).
*   **IPC:** AIDL (Android Interface Definition Language) for defining system-wide interfaces and generating C++ bindings.

## Reference & Interoperability
*   **Reference Language:** Java (Sources used as the functional baseline for C++ reimplementation).
*   **Android NDK:** Version r29 (Primary development kit for compiling and linking native framework components).

## Testing & Validation
*   **Testing Framework:** GoogleTest (gtest) and GoogleMock (gmock) for unit and integration testing.
*   **Build System (Tests):** CMake (Used specifically for building and managing the testing suites).
*   **Validation Suite:** Android Compatibility Test Suite (CTS) for ensuring platform compliance.

## Architectural Patterns
*   **Asynchronous Primitives:** C++23 Coroutines for non-blocking operations.
*   **Error Handling:** `std::expected` for type-safe, recoverable error reporting.
*   **Resource Management:** Strict RAII and smart pointer ownership.
