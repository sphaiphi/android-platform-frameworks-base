# Implementation Plan - Activity Component Implementation (Core)

## Phase 1: Context and Application Foundation [checkpoint: 23ddc08]

- [x] Task: Implement `ContextImpl` 85d43a8
    - [x] Spec Analysis: Review `core/cpp/specs/android/app/ContextImpl.md` and clarify system service access patterns.
    - [x] Unit Testing: Write failing tests for `getSystemService`, `getPackageName`, and directory access (`getFilesDir`, `getCacheDir`).
    - [x] Implementation: Implement `ContextImpl` using C++23 standards, ensuring RAII for resource management.
    - [x] Verification: Pass unit tests and verify >80% coverage.
- [x] Task: Implement `ActivityThread` Foundation e9cb820
    - [x] Spec Analysis: Review `core/cpp/specs/android/app/ActivityThread.md` focusing on the main loop and `bindApplication`.
    - [x] Unit Testing: Write failing tests for main looper initialization and application binding sequence.
    - [x] Implementation: Implement `ActivityThread basics and the H handler for message processing.
    - [x] Verification: Pass unit tests.
- [x] Task: Conductor - User Manual Verification 'Context and Application Foundation' (Protocol in workflow.md)

## Phase 2: Activity Lifecycle and Instrumentation [checkpoint: 5e60a1b]

- [x] Task: Implement `Activity` Core f3e9c09
    - [x] Spec Analysis: Review `core/cpp/specs/android/app/Activity.md` focusing on state transitions and Intent storage.
    - [x] Unit Testing: Write failing tests for lifecycle methods (`onCreate` -> `onDestroy`) and Intent handling (`getIntent`/`setIntent`).
    - [x] Implementation: Implement the `Activity` class and its state management logic.
    - [x] Verification: Pass unit tests.
- [x] Task: Implement `Instrumentation` Core fbe98e0
    - [x] Spec Analysis: Review `core/cpp/specs/android/app/Instrumentation.md`.
    - [x] Unit Testing: Write failing tests for `newActivity` and `callActivityOnCreate`/`callActivityOnResume` hooks.
    - [x] Implementation: Implement `Instrumentation` to drive Activity lifecycle events.
    - [x] Verification: Pass unit tests.
- [x] Task: Conductor - User Manual Verification 'Activity Lifecycle and Instrumentation' (Protocol in workflow.md)

## Phase 3: Integration and Validation [checkpoint: 779735f]

- [x] Task: Implement Activity Scheduling in `ActivityThread` f4477ea
    - [x] Unit Testing: Write failing integration tests for `handleLaunchActivity` flow (creating Activity and moving to RESUMED state).
    - [x] Implementation: Integrate `ActivityThread` with `Instrumentation` and `ContextImpl` to launch and manage Activities.
    - [x] Verification: Pass integration tests.
- [x] Task: CTS Validation for Activity Components 875e7c3
    - [x] CTS Testing: Port/write CTS tests in `cts/cpp/tests` for activity lifecycle compliance and context functionality.
    - [x] Verification: Pass CTS validation suite.
- [x] Task: Conductor - User Manual Verification 'Integration and Validation' (Protocol in workflow.md)
