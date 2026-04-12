---
name: android-ndk-coding
description: Expertise in Android Native Development Kit (NDK) coding and Stable AIDL (NDK backend). Use when writing C++ logic, JNI bridges, or implementing high-performance IPC via Binder. Trigger when the user mentions JNI, .so libraries, CMake, or AIDL with NDK/C++ backends.
license: MIT
compatibility: Requires Android NDK (r21+ for Stable AIDL), CMake (3.22.1+), and libbinder_ndk.
metadata:
  category: mobile-development
  specialization: performance-optimization-ipc
---

# Android NDK & Stable AIDL Coding Skill

## Overview
This skill enables the agent to architect native Android components and cross-process interfaces. It specifically handles the transition from traditional JNI to modern, stable C++ Binder interfaces using the AIDL NDK backend.

## When to Use This Skill
- **Native Logic:** Performance-critical C++ algorithms and library porting.
- **JNI Integration:** Standard bridging between Kotlin/Java and C++.
- **Stable AIDL (NDK Backend):** Defining `.aidl` interfaces that generate C++ headers for system services or app-to-app IPC.
- **Build Systems:** Configuring `CMakeLists.txt` and `build.gradle` for `externalNativeBuild` and AIDL generation.

## Core Instructions

### 1. Stable AIDL & NDK Backend
- **Build Configuration:** Ensure `build.gradle` specifies the NDK backend:
  ```gradle
  aidl {
      genSet {
          ndk { enabled true }
      }
  }
  ```
- **Memory Management:** Use `ndk::SharedRefBase` for binder objects. Always wrap implementation classes in `ndk::SharedRefBase::make<MyInterface>()`.
- **Error Handling:** Use `ndk::ScopedAStatus` for returning errors across the binder boundary. Avoid throwing C++ exceptions.
- **Threading:** Remember that Binder calls arrive on a thread pool; ensure thread safety in the C++ implementation.

### 2. JNI Implementation Standards
- Use `extern "C" JNIEXPORT ... JNICALL` for exported functions.
- **Naming:** Follow `Java_package_name_ClassName_methodName`.
- **References:** Strictly manage `jobject` life cycles. Use `env->DeleteLocalRef` in loops to prevent table overflow.

### 3. CMake & Native Linking
- Link the AIDL-generated library and `libbinder_ndk` in `CMakeLists.txt`:
  ```cmake
  # Example linking
  target_link_libraries(${target_name} binder_ndk)
  ```
- Use `find_library(log-lib log)` for Android logging.

## Recommended Directory Structure
- `aidl/`: Store `.aidl` interface definitions.
- `jni/`: Standard JNI bridge code.
- `native/`: Core C++ logic and AIDL implementation classes.
- `references/BINDER_GUIDE.md`: Notes on `AIBinder` and parcelables.

## Best Practices
- **Prefer Stable AIDL:** Use the NDK backend over manual JNI for IPC to gain type safety and easier maintenance.
- **RAII:** Always use `std::unique_ptr` or `std::shared_ptr` for non-binder native resources.
- **ABI Filtering:** Limit builds to `arm64-v8a` and `x86_64` in `build.gradle` to keep APK sizes manageable.

## Validation Checklist
- [ ] Does the `.aidl` file have the `ndk` backend enabled?
- [ ] Is the C++ implementation inheriting from the generated `Bn[InterfaceName]`?
- [ ] Are all binder objects managed via `ndk::SharedRefBase`?
- [ ] Are `ScopedAStatus` checks performed on the client side?
- [ ] Is `libbinder_ndk` included in the `target_link_libraries`?
