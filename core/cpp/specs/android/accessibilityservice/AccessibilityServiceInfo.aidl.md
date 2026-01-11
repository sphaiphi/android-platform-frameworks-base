
# AccessibilityServiceInfo.aidl - Reverse Engineering Documentation

## Executive Summary
This AIDL file declares the `AccessibilityServiceInfo` class as a `parcelable`. This registration allows instances of `AccessibilityServiceInfo` to be serialized and deserialized for transport across process boundaries using the Binder IPC framework.

## Architecture Overview
*   **AIDL Declaration**: The `parcelable AccessibilityServiceInfo;` line informs the AIDL toolchain that `AccessibilityServiceInfo` is a custom type that knows how to write and read itself from a `Parcel`. This allows the class to be used as a parameter or return type in any AIDL interface.
*   **NDK Header**: The `ndk_header "android/accessibilityservice"` directive indicates that the C++ version of this parcelable is defined within a header file located in the `android/accessibilityservice` directory of the NDK or a corresponding native include path. This enables interoperability between Java and native C++ code.

## Java-to-C++ Translation Guide
*   **Parcelable Contract**: This file mandates that a C++ version of `AccessibilityServiceInfo` must exist and must implement the `Parcelable` contract in a way that is perfectly wire-compatible with the Java implementation.
*   **C++ Implementation**: The corresponding C++ class must have `readFromParcel()` and `writeToParcel()` methods that serialize and deserialize the exact same sequence of data types as the Java `AccessibilityServiceInfo` class. The analysis in the `AccessibilityServiceInfo.java.md` file provides the detailed field order required for this implementation.

## Implementation Risks
*   The key risk is a mismatch between the Java and C++ `Parcelable` implementations. As documented for `AccessibilityServiceInfo.java`, this class has many fields, and any deviation in their order or type during serialization will break IPC and cause crashes or data corruption.
