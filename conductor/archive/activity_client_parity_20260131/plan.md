# Implementation Plan - ActivityClient Parity Update

This plan outlines the steps to bring the C++ `ActivityClient` into parity with `ActivityClient.java`, excluding specialized services as defined in the spec.

## Phase 1: Interface & Error Handling Definition [checkpoint: 4a6f9ce]
Define the expanded AIDL-like interface and the error reporting mechanism.

- [x] Task: Define `ActivityError` enum and integration with `std::expected`. [ac1e2f3]
    - [x] Define `ActivityError` in a suitable header (e.g., `ActivityCommon.h` or within `ActivityClient.h`).
    - [x] Add error codes for `BINDER_ERROR`, `SERVICE_NOT_FOUND`, and `INVALID_TOKEN`.
- [x] Task: Expand `IActivityClientController` interface in `ActivityClient.h`. [59e0817]
    - [x] Add all scoped methods from the spec to the virtual interface.
    - [x] Update existing methods to return `void` or appropriate types matching Java return values.
- [x] Task: Conductor - User Manual Verification 'Phase 1: Interface & Error Handling Definition' (Protocol in workflow.md) [a9109c5]

## Phase 2: Lifecycle & Task Management Implementation (Red/Green) [checkpoint: 5619349]

- [ ] Task: Implement Lifecycle Reporting methods.
    - [ ] **Red Phase**: Update `ActivityClient_test.cpp` to expect calls for `activityIdle`, `activityRefreshed`, etc., returning `std::expected`.
    - [ ] **Green Phase**: Update `ActivityClient.h/cpp` to proxy these calls to the interface.
- [ ] Task: Implement Task & Stack Management methods.
    - [ ] **Red Phase**: Add tests for `finishActivityAffinity`, `moveActivityTaskToBack`, `isTopOfTask`, etc.
    - [ ] **Green Phase**: Implement the proxy logic in `ActivityClient.cpp`.
- [x] Task: Conductor - User Manual Verification 'Phase 2: Lifecycle & Task Management Implementation' (Protocol in workflow.md) [5619349]

## Phase 3: Information Retrieval & Configuration (Red/Green) [checkpoint: 54ea5b4]

- [ ] Task: Implement Activity Information retrieval methods.
    - [ ] **Red Phase**: Add tests for `getDisplayId`, `getCallingPackage`, `getLaunchedFromUid`, etc.
    - [ ] **Green Phase**: Implement the proxy logic and ensure proper handling of optional return values (e.g., `std::optional` or `std::expected`).
- [ ] Task: Implement Configuration & Windowing methods.
    - [ ] **Red Phase**: Add tests for `setRequestedOrientation`, `setTaskDescription`, `setImmersive`, etc.
    - [ ] **Green Phase**: Implement the proxy logic.
- [x] Task: Conductor - User Manual Verification 'Phase 3: Information Retrieval & Configuration' (Protocol in workflow.md) [54ea5b4]

## Phase 4: Transitions & Singleton Refinement [checkpoint: 013e137]
Implement animation hooks and finalize the singleton logic.

- [ ] Task: Implement Transitions & Animations methods.
    - [ ] **Red Phase**: Add tests for `overrideActivityTransition`, `registerRemoteAnimations`, etc.
    - [ ] **Green Phase**: Implement the proxy logic.
- [ ] Task: Refine `ActivityClient` Singleton and lazy initialization.
    - [ ] **Red Phase**: Write a test verifying that `getInstance()` initializes the interface only when needed (if mockable) or handles a null interface gracefully.
    - [ ] **Green Phase**: Finalize `ensure_interface_selected` logic to fetch from `ActivityTaskManager` (once available) or keep as a TODO with robust null checks.
- [x] Task: Conductor - User Manual Verification 'Phase 4: Transitions & Singleton Refinement' (Protocol in workflow.md) [013e137]

## Phase 5: Verification & Integration [checkpoint: ccc7ad5]
Final build check and test execution.

- [ ] Task: Verify compilation and run unit tests.
    - [ ] Execute `cmake --build build --target ActivityClient_test`.
    - [ ] Run the generated test binary.
- [x] Task: Conductor - User Manual Verification 'Phase 5: Verification & Integration' (Protocol in workflow.md) [ccc7ad5]
