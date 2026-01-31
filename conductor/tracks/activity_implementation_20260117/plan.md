# Plan: Implement Activity

## Phase 1: Spec Analysis & Context Integration [checkpoint: 3f1e6df]
- [x] Task: Spec Analysis & Update for `Activity.md` cef65ee
    - [x] Read `core/cpp/specs/android/app/Activity.md`.
    - [x] Update spec to clarify Context inheritance and lifecycle state machine.
    - [x] Define the public API surface in C++.
- [x] Task: Conductor - User Manual Verification 'Spec Analysis & Context Integration' (Protocol in workflow.md) (manual)

## Phase 2: Core Lifecycle TDD & Implementation [checkpoint: eccc054]
- [x] Task: Implement `Activity` Lifecycle (TDD) 897397a
    - [x] Create `core/cpp/android/app/Activity_test.cpp`.
    - [x] Write failing tests for `onCreate`, `onStart`, `onResume`, `onPause`, `onStop`, `onDestroy`.
    - [x] Implement `core/cpp/android/app/Activity.hpp` and `Activity.cpp` to pass tests.
    - [x] Refactor for C++23 safety (e.g., using `std::expected` for lifecycle errors).
- [x] Task: Conductor - User Manual Verification 'Core Lifecycle TDD & Implementation' (Protocol in workflow.md) (manual)

## Phase 3: Context & Service Integration [checkpoint: 86f4ca2]
- [x] Task: Implement `Activity` Context Features (TDD) eaf361e
    - [x] Add tests for `Activity` accessing `Context` methods (e.g., `getSystemService`).
    - [x] Implement Context delegation/inheritance logic in `Activity`.
    - [x] Verify proper resource cleanup and ownership.
- [x] Task: Conductor - User Manual Verification 'Context & Service Integration' (Protocol in workflow.md) (manual)

## Phase 4: CTS Validation [checkpoint: ebf99cd]
- [x] Task: Port Activity CTS Tests 6efdd64
    - [x] Analyze `cts/java/tests/app/src/android/app/cts/LifecycleTest.java`.
    - [x] Create `cts/cpp/tests/android/app/ActivityCtsTest.cpp`.
    - [x] Implement test cases mirroring the Java CTS logic.
    - [x] Verify compliance with standard Android behavior.
- [x] Task: Conductor - User Manual Verification 'CTS Validation' (Protocol in workflow.md) (manual)
