# Implementation Plan - Remaining App Module Implementation

This plan outlines the steps to implement the remaining core `android.app` components in C++, ensuring parity with Java references and adherence to existing specifications.

## Phase 1: Lifecycle & Execution Components
Implement the fundamental classes for application execution and lifecycle monitoring.

- [x] Task: Implement `ActivityThread`. 664f94f
    - [x] **Red Phase**: Write failing unit tests for `ActivityThread` main loop and activity record management in `ActivityThread_test.cpp`.
    - [x] **Green Phase**: Implement `ActivityThread.h` and `ActivityThread.cpp` to pass tests, focusing on the message handling and state synchronization logic.
- [x] Task: Implement `Instrumentation`. 417e00c
    - [x] **Red Phase**: Define tests for activity monitoring and lifecycle hooks in `Instrumentation_test.cpp`.
    - [x] **Green Phase**: Implement `Instrumentation.cpp` following the C++ spec and Java baseline.
- [x] Task: Implement `Application`. 9403404
    - [x] **Red Phase**: Write tests for application lifecycle events (`onCreate`, `onTerminate`, etc.).
    - [x] **Green Phase**: Implement the `Application` base class and its integration with `Context`.
- [x] Task: Implement `ActivityGroup` & `AliasActivity`. dc1b539
    - [x] **Red Phase**: Define baseline behavior tests for legacy activity containment and alias resolution.
    - [x] **Green Phase**: Implement minimal functional versions according to specifications.

## Phase 2: Management & IPC Interfaces
Implement the interfaces for interacting with system-level management services.

- [x] Task: Implement `ActivityTaskManager` & `ActivityManager`. a5b0eb7
    - [x] **Red Phase**: Write failing tests for service retrieval and task/process info querying.
    - [x] **Green Phase**: Implement proxy classes and IPC logic utilizing the generated AIDL bindings.
- [x] Task: Implement `IActivityClientController` & `AppOpsManager`. a5b0eb7
    - [x] **Red Phase**: Define tests for client-side controller logic and application operation tracking.
    - [x] **Green Phase**: Implement the native interfaces and matching Java logic for ops tracking.

## Phase 3: Data & Configuration Containers
Batch implementation of parcelable data structures and configuration objects.

- [x] Task: Implement Configuration & Info classes. a65b1b9
    - [x] **Red Phase**: Write unit tests for parceling and data integrity for `TaskInfo`, `WindowConfiguration`, `ApplicationStartInfo`, and `ApplicationErrorReport`.
    - [x] **Green Phase**: Implement the data structures and serialization logic.
- [x] Task: Implement Option & Action classes. a65b1b9
    - [x] **Red Phase**: Define tests for `ActivityOptions`, `ActivityTransition`, and `AsyncNotedAppOp`.
    - [x] **Green Phase**: Implement components to match Java functional baseline.
- [x] Task: Implement `Notification` structure. a65b1b9
    - [x] **Red Phase**: Write tests for notification builder patterns and complex parceling logic.
    - [x] **Green Phase**: Implement the `Notification` class and related nested data structures.

## Phase 4: Integration & System Verification
Final validation against system standards and stress testing.

- [x] Task: Lifecycle Stress Testing. 93b2ad0
    - [x] Create and execute test suites that simulate rapid activity/application transitions to verify state machine stability.
- [x] Task: CTS Compliance Verification. 93b2ad0
    - [x] Execute relevant CTS tests from `cts/cpp/tests` against the new implementations.
    - [x] Port any missing Java CTS checks to verify full platform parity.
- [x] Task: Overall Build & Performance Audit. 93b2ad0
    - [x] Verify that all components compile with `-std=c++23` and meet performance targets.
