# Technology Stack

## Core Framework (Native)
*   **Primary Language:** Modern C++ (Standard: C++23)
      * Reference: https://cppreference.com/w/cpp/23.html
*   **Safety Standards:** C++ Core Guidelines, Safety-First Idioms (Type, Bounds, Lifetime, Init, Error).
*   **Build System:** `ndk-build` (utilizing `Android.mk` scripts for system-level integration).
*   **IPC:** AIDL (Android Interface Definition Language) for defining system-wide interfaces and generating C++ bindings.

## Reference & Interoperability
*   **Reference Language:** Java (Sources used as the functional baseline for C++ reimplementation).
*   **Android NDK:** Version r29 (Primary development kit for compiling and linking native framework components), 
      * Path:$ANDROID_NDK_HOME
      * Reference: https://developer.android.com/ndk/reference

## Testing & Validation
*   **Testing Framework:** GoogleTest (gtest) and GoogleMock (gmock) for unit and integration testing.
*   **Build System (Tests):** CMake (Used specifically for building and managing the testing suites).
*   **Validation Suite:** Android Compatibility Test Suite (CTS) for ensuring platform compliance.

## Architectural Patterns
*   **Asynchronous Primitives:** C++23 Coroutines for non-blocking operations.
*   **Error Handling:** `std::expected` for type-safe, recoverable error reporting.
*   **Resource Management:** Strict RAII and smart pointer ownership.

## Warning

libbinder_ndk has two sets of headers. For platform devs, these are shipped together, but if you are an application developer, you need to include (usually with -I for C++ compilers, such as clang) them from different places. The core headers for APIs that are provided on-device (such as android/binder_ibinder.h, defined in the Android tree at frameworks/native/libs/binder/ndk/include_ndk) are shipped with the NDK. However, other helper files (such as android/binder_interface_utils.h, defined in the Android tree frameworks/native/libs/binder/ndk/include_cpp) provide C++ utilities that are required to use with the AIDL compiler and shipped with it in the SDK under platforms/$PLATFORM_NAME/optional/libbinder_ndk_cpp/.