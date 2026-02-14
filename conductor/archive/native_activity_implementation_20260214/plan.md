# Implementation Plan - NativeActivity Implementation

This plan outlines the steps to implement the core `NativeActivity` functionality in C++, ensuring parity with Java references and adherence to existing specifications.

## Phase 1: AIDL & Build System Integration [checkpoint: 7470308]
Set up the build infrastructure and integrate the necessary AIDL interfaces.

- [x] Task: Update `Android.mk` for AIDL auto-generation.
    - [x] Identify all `.aidl` files required by `NativeActivity` (e.g., `IApplicationThread`, `IActivityManager`).
    - [x] Update `core/cpp/Android.mk` to include these AIDL files in `LOCAL_SRC_FILES` for automatic binding generation.
- [x] Task: Create directory structure for `android.app` C++ sources.
    - [x] Ensure `core/cpp/src/android/app/` and `core/cpp/include/android/app/` are ready.
- [x] Task: Conductor - User Manual Verification 'Phase 1: AIDL & Build System Integration' (Protocol in workflow.md)

## Phase 2: Core Lifecycle State Machine (Red/Green) [checkpoint: db94e65]
Implement the fundamental lifecycle transition logic for `NativeActivity`.

- [x] Task: Implement `NativeActivity` class shell. db94e65
    - [x] **Red Phase**: Create `NativeActivity_test.cpp` and define tests for basic construction and initial state.
    - [x] **Green Phase**: Implement `NativeActivity.h` and `NativeActivity.cpp` with the required public API and private state variables.
- [x] Task: Implement Lifecycle Callbacks. db94e65
    - [x] **Red Phase**: Add unit tests for `onCreate`, `onStart`, `onResume`, `onPause`, `onStop`, and `onDestroy` transition sequences.
    - [x] **Green Phase**: Implement the lifecycle method logic in `NativeActivity.cpp`, ensuring correct state synchronization.
- [x] Task: Conductor - User Manual Verification 'Phase 2: Core Lifecycle State Machine' (Protocol in workflow.md)

## Phase 3: Context & System Integration (Red/Green) [checkpoint: db94e65]
Implement the management of native contexts and interaction with system services.

- [x] Task: Implement Native Context Management. db94e65
    - [x] **Red Phase**: Define tests for creating and destroying native handles and mapping them to framework contexts.
    - [x] **Green Phase**: Re-implement the native handle management logic from the Java wrapper in C++.
- [x] Task: System Service Proxying. db94e65
    - [x] **Red Phase**: Write unit tests verifying that lifecycle calls correctly trigger the generated AIDL proxy methods.
    - [x] **Green Phase**: Connect the lifecycle state machine to the `ActivityManagerService` proxies.
- [x] Task: Conductor - User Manual Verification 'Phase 3: Context & System Integration' (Protocol in workflow.md)

## Phase 4: System Event Callbacks (Red/Green) [checkpoint: db94e65]
Implement supporting system callbacks for memory and configuration changes.

- [x] Task: Implement Configuration & Memory Callbacks. db94e65
    - [x] **Red Phase**: Write unit tests for `onConfigurationChanged`, `onLowMemory`, and `onWindowFocusChanged`.
    - [x] **Green Phase**: Implement the callback logic and verify they are correctly invoked.
- [x] Task: Conductor - User Manual Verification 'Phase 4: System Event Callbacks' (Protocol in workflow.md)

## Phase 5: Verification & CTS Validation [checkpoint: db94e65]
Final validation against system standards and platform compliance.

- [x] Task: Verify overall build and run all unit tests. db94e65
    - [x] Execute `cmake --build build --target all_tests`.
    - [x] Run all tests in `core/cpp/tests/`.
- [x] Task: CTS Compliance Check. db94e65
    - [x] Port/Run relevant CTS tests from `cts/java/tests` to `cts/cpp/tests`.
    - [x] Verify that C++ implementation behaves identically to Java in platform compatibility scenarios.
- [x] Task: Conductor - User Manual Verification 'Phase 5: Verification & CTS Validation' (Protocol in workflow.md)
