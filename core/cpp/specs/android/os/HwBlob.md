# HwBlob - Reverse Engineering Documentation

## Executive Summary
`HwBlob` represents a fixed-size block of memory used in HIDL transactions (`HwParcel`). It maps to `hardware::hidl_blob` in C++. It allows reading/writing primitives and embedded objects (like handles) at specific offsets.

## Architecture Overview
-   **Role**: HIDL Memory Buffer / Struct Wrapper.
-   **Allocation**: Native allocation via `NativeAllocationRegistry`.
-   **Usage**: Used to marshal structs, vectors, and strings in HIDL.

## API Reference
-   **Getters/Setters**: `getBool`, `getInt32`, `getString`, `putInt64`, etc. taking an byte `offset`.
-   **Arrays**: `copyToInt32Array`, `putInt32Array` for bulk transfer.
-   **Embedded Objects**: `putNativeHandle`, `putHidlMemory`, `putBlob`.

## Java-to-C++ Translation Guide
-   **Equivalent**: `android::hardware::hidl_blob`.
-   **Memory Layout**: The offsets used in Java must exactly match the C++ struct layout (including padding/alignment) defined by the HIDL interface.
-   **String**: `getString` reads a `hidl_string` struct (size + buffer ptr) and dereferences it.

## Implementation Risks
-   **Alignment**: HIDL enforces strict alignment. Java code (usually generated) must calculate offsets correctly.
-   **Buffer Safety**: `HwBlob` access is bounds-checked in JNI, but incorrect offsets will read garbage.
