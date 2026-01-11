
# AccessibilityGestureEvent.aidl - Reverse Engineering Documentation

## Executive Summary
This AIDL file declares the `AccessibilityGestureEvent` class as a `parcelable`. This declaration is what allows objects of this class to be passed across process boundaries using Android's Binder IPC framework.

## Architecture Overview
*   **AIDL Declaration**: The `parcelable` keyword in AIDL instructs the AIDL compiler to recognize this class as something that can be marshaled and unmarshaled. It does not generate the class itself, but it allows other AIDL interfaces to use `AccessibilityGestureEvent` as a parameter or return type.
*   **NDK Header**: The `ndk_header "android/accessibilityservice/AccessibilityGestureEvent.h"` directive is a crucial instruction for the AIDL compiler. It specifies that there is a corresponding C++ header file available for the NDK. This enables the `parcelable` to be used not only between Java services but also between Java and native (C++) components.

## Java-to-C++ Translation Guide
*   **Parcelable Contract**: The existence of this file, especially with the `ndk_header` directive, confirms that a C++ version of `AccessibilityGestureEvent` is intended to exist and that it must have a `Parcelable` implementation that is wire-compatible with the Java version.
*   **Header Location**: The C++ header file should be located at `android/accessibilityservice/AccessibilityGestureEvent.h` within the NDK includes or a similar include path for the target build system.
*   **Implementation**: The C++ class must implement the necessary `readFromParcel()` and `writeToParcel()` methods to match the data serialization order of the Java `AccessibilityGestureEvent` class.

## Implementation Risks
*   The primary purpose of this file is to enforce the `Parcelable` contract. The main risks are associated with implementing the `Parcelable` logic itself in the corresponding `.java` and `.h`/`.cpp` files, as detailed in the documentation for `AccessibilityGestureEvent.java`. Any mismatch will break IPC.
