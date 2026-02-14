# Specification - NativeActivity Implementation

## Overview
This track involves implementing the core `NativeActivity` functionality within the C++ `android.app` module. The goal is to provide a native implementation of the activity lifecycle and management logic, enabling native applications to bypass JNI overhead while maintaining full compatibility with the Android system's activity management services.

## Functional Requirements
- **Lifecycle Implementation**: Implement the complete state machine for `NativeActivity`, including:
    - `onCreate`, `onStart`, `onResume`, `onPause`, `onStop`, `onDestroy`.
    - `onConfigurationChanged`, `onLowMemory`, `onWindowFocusChanged`.
- **System Service Integration**: Ensure proper interaction with `ActivityManagerService` via AIDL-generated interfaces.
- **Build System Integration**: Update `core/cpp/Android.mk` to include relevant `.aidl` files for automatic C++ binding generation.
- **Native Context Management**: Re-implement the `NativeActivity` native handle and context management logic currently found in the Java wrapper.

## Non-Functional Requirements
- **C++23 Standards**: Utilize modern C++ features for state management and error handling.
- **Minimal Overhead**: Ensure the native implementation is highly efficient, specifically targeting zero-cost lifecycle transitions.
- **Thread Safety**: Manage lifecycle transitions safely across the main UI thread and binder callback threads.

## Acceptance Criteria
1.  C++ implementation of `NativeActivity` and its associated internal management classes.
2.  `Android.mk` updated and building successfully with AIDL integration.
3.  Unit tests in `core/cpp/tests/` verifying lifecycle transitions and state synchronization.
4.  Compliance with existing C++ specifications in `@core/cpp/specs/android/app/`.

## Out of Scope
- Implementation of higher-level UI widgets (e.g., Fragments) within the native layer.
- Modification of the system server (AMS) logic.
