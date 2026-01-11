# Specification: Native Intent and Bundle Core

## Overview
Implement the core `android::content::Intent` and `android::os::Bundle` components in modern C++23. These components are fundamental to the Android application model and must provide high-performance, type-safe alternatives to the Java implementations.

## Functional Requirements

### 1. `android::os::Bundle` (C++23)
*   **Key-Value Store:** Support storing and retrieving various data types (int, long, double, string, boolean, and nested Bundles).
*   **Type Safety:** Use `std::variant` or a custom type-safe union for value storage.
*   **Interoperability:** Provide methods to serialize/deserialize for IPC (AIDL integration).
*   **Parity:** Match the functional behavior of `android.os.Bundle` (Java).

### 2. `android::content::Intent` (C++23)
*   **Action & Data:** Support setting and getting the Intent action, data URI, and MIME type.
*   **Extras:** Integrate with `android::os::Bundle` for passing extras.
*   **Flags:** Support standard Intent flags.
*   **Component Name:** Support explicit Intent targeting via component names.
*   **Parity:** Match the functional behavior of `android.content.Intent` (Java).

## Non-Functional Requirements
*   **C++23 Modernity:** Use `std::expected` for error handling, `std::span` for collections, and concepts for template constraints.
*   **Safety:** Adhere to the five safety dimensions (Type, Bounds, Lifetime, Initialization, Error Handling).
*   **Zero-Cost Abstractions:** Ensure that using these C++ classes has minimal overhead.
*   **Performance:** Faster serialization/deserialization compared to JNI-based calls.

## Acceptance Criteria
*   Unit tests cover >80% of the code.
*   Successfully passes relevant CTS tests (integrated with the CMake build).
*   All public APIs documented.
