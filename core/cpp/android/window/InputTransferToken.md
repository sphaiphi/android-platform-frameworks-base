# InputTransferToken - Reverse Engineering Documentation

## Executive Summary
`InputTransferToken` is a wrapper around a native token used to identify an input channel or surface for the purpose of transferring touch gestures (e.g., from SystemUI to an App).

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: Opaque Handle / Native Wrapper.

## Detailed Functionality

### Native Integration
*   `mNativeObject`: `long` (pointer).
*   **Native Methods**: `nativeCreate`, `nativeWriteToParcel`, `nativeReadFromParcel`, `nativeGetBinderToken`.
*   **Lifecycle**: Uses `NativeAllocationRegistry` to clean up the native object when the Java object is GC'd.

### Public API
*   `getToken()`: Returns the IBinder associated with the native token.
*   `equals/hashCode`: Delegated to native.

## Java-to-C++ Translation Guide

### Wrapper Nature
*   This Java class is *already* just a JNI wrapper.
*   The C++ implementation of this class *is* the logic.
*   **Action**: Locate the underlying C++ `InputTransferToken` (likely in `frameworks/native` or `frameworks/base/core/jni`). The "Translation" here effectively means "Use the existing C++ class".

## Implementation Risks
*   **None**: It's a handle.
