# InputApplicationHandle - Reverse Engineering Documentation

## Executive Summary
`InputApplicationHandle` is an opaque handle representing an entire application that can receive input. It allows the native input dispatcher to refer to an application's window token and configuration without directly exposing the `WindowManager`'s internal state.

## Architecture Overview
*   **Role**: Application-level input identifier.
*   **JNI Centric**: Wraps a native C++ `InputApplicationHandle`.
*   **Lifecycle**: Managed via `nativeDispose()` in the finalizer.

## Data Model
*   **`token`**: `IBinder` - The unique identifier for the application (usually the `Activity` token).
*   **`name`**: `String` - A descriptive name for debugging (e.g., the package name).
*   **`dispatchingTimeoutMillis`**: `long` - The time allowed for the application to process input before an ANR (Application Not Responding) is triggered.

## Java-to-C++ Translation Guide
*   **Native Equivalent**: Wrap `android::InputApplicationHandle`.
*   **Binder**: The `token` maps to `sp<IBinder>`.

## Implementation Risks
*   **ANR Calculation**: The timeout provided here is the definitive value used by the kernel-level input dispatcher.
