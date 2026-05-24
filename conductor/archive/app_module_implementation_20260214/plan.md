# Implementation Plan - App Module Implementation

This plan outlines the steps to implement the core `android.app` components in C++, ensuring parity with Java references and adherence to existing specifications.

## Phase 1: AIDL & Build System Integration [checkpoint: 4779242]
Set up the build infrastructure and integrate the necessary AIDL interfaces.

- [x] Task: Update `Android.mk` for AIDL auto-generation.
    - [x] Identify all `.aidl` files required by the core components (ActivityManager, ActivityThread, etc.).
    - [x] Update `core/cpp/Android.mk` to include these AIDL files in the `LOCAL_SRC_FILES` or via the appropriate NDK AIDL generator.
- [x] Task: Create directory structure for `android.app` C++ sources.
    - [x] Ensure `core/cpp/src/android/app/` and `core/cpp/include/android/app/` are ready.
- [x] Task: Conductor - User Manual Verification 'Phase 1: AIDL & Build System Integration' (Protocol in workflow.md)

## Phase 2: Core Lifecycle Components (Red/Green) [checkpoint: 1234295]
Implement the fundamental classes for activity management and execution.

- [x] Task: Implement `Activity` class. 169c74a
    - [x] **Red Phase**: Create `Activity_test.cpp` and define tests for lifecycle callbacks (`onCreate`, `onStart`, `onResume`, etc.).
    - [x] **Green Phase**: Implement `Activity.h` and `Activity.cpp` to satisfy tests and match `Activity.java` logic.
- [x] Task: Implement `ActivityThread` & `Instrumentation`. 169c74a
    - [x] **Red Phase**: Write tests for main loop integration and event injection in `ActivityThread_test.cpp` and `Instrumentation_test.cpp`.
    - [x] **Green Phase**: Implement the proxy logic and thread management in `ActivityThread.cpp` and `Instrumentation.cpp`.
- [x] Task: Conductor - User Manual Verification 'Phase 2: Core Lifecycle Components' (Protocol in workflow.md)

## Phase 3: Management & IPC Interfaces (Red/Green) [checkpoint: 169ba0d]
Implement the interfaces for interacting with system services.

- [x] Task: Implement `ActivityManager` & `IActivityClientController`. 96601d4
    - [x] **Red Phase**: Add tests for service retrieval and IPC call proxying.
    - [x] **Green Phase**: Implement the implementation/proxy classes using the generated AIDL bindings.
- [x] Task: Implement `TaskStackListener`. 96601d4
    - [x] **Red Phase**: Write tests for task change notifications.
    - [x] **Green Phase**: Implement the listener interface and registration logic.
- [x] Task: Conductor - User Manual Verification 'Phase 3: Management & IPC Interfaces' (Protocol in workflow.md)

## Phase 4: Supporting App Components Implementation (Red/Green) [checkpoint: 85b2255]
Batch implementation of supporting classes identified in the spec.

- [x] Task: Implement Exception classes (e.g., `ServiceStartNotAllowedException`, `RecoverableSecurityException`). 33d8c9f
    - [x] **Red Phase**: Write unit tests for exception propagation and message handling.
    - [x] **Green Phase**: Implement the exception hierarchy in C++.
- [x] Task: Implement Info & Configuration classes (e.g., `TaskInfo`, `WindowConfiguration`, `ApplicationStartInfo`). 33d8c9f
    - [x] **Red Phase**: Add tests for parceling/unparceling and data integrity.
    - [x] **Green Phase**: Implement the data structures and matching Java logic.
- [x] Task: Implement remaining supporting classes (Fragments, Loaders, Managers). 33d8c9f
    - [x] **Red Phase**: Define baseline behavior tests for each.
    - [x] **Green Phase**: Implement logic according to `.md` specs and Java source.
- [x] Task: Conductor - User Manual Verification 'Phase 4: Supporting App Components Implementation' (Protocol in workflow.md)

## Phase 5: Verification & CTS Validation [checkpoint: d83df5d]
Final validation against system standards.

- [x] Task: Verify overall build and run all unit tests. 7b51703
    - [x] Execute `cmake --build build --target all_tests`.
    - [x] Run all tests in `core/cpp/tests/`.
- [x] Task: CTS Compliance Check. 85b2255
    - [x] Port/Run relevant CTS tests from `cts/java/tests` to `cts/cpp/tests`.
    - [x] Verify that C++ implementations behave identically to Java in platform compatibility scenarios.
- [x] Task: Conductor - User Manual Verification 'Phase 5: Verification & CTS Validation' (Protocol in workflow.md)
