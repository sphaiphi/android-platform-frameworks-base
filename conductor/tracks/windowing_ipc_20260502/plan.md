# Implementation Plan - Core Windowing IPC (IWindowSession)

This plan outlines the steps to implement the core IPC session layer between `ViewRootImpl` and the system's Window Manager.

## Phase 1: AIDL Generation & Skeleton [checkpoint: 038fdd21]
Establish the Binder interface and the initial class structure.

- [x] Task: Generate C++ bindings for `IWindowSession.aidl`. `f94c4553`
    - [x] **Spec Analysis**: Review `IWindowSession.aidl` and identify all required parcelables (`WindowRelayoutResult`, `InsetsState`, etc.).
    - [x] **Implementation**: Run the AIDL compiler to generate the NDK backend headers and sources in `core/cpp/`.
- [x] Task: Implement `WindowSession` skeleton. `f94c4553`
    - [x] **Red Phase**: Write unit tests verifying that a `WindowSession` instance can be created and cast to its Binder interface.
    - [x] **Green Phase**: Create `core/cpp/src/android/view/WindowSession.cpp` inheriting from `BnWindowSession` with stubbed implementations.
- [ ] Task: Conductor - User Manual Verification 'Phase 1: AIDL & Skeleton' (Protocol in workflow.md)

## Phase 2: Window Registration (`addToDisplay`)
Enable windows to register themselves with the session.

- [x] Task: Implement `addToDisplay` logic. `e7c21715`
    - [x] **Red Phase**: Write tests verifying that `addToDisplay` correctly populates output parameters like `AParcel` for `InsetsState` and `InputChannel`.
    - [x] **Green Phase**: Implement registration tracking and initial state return logic in `WindowSession`.
- [ ] Task: Conductor - User Manual Verification 'Phase 2: Window Registration' (Protocol in workflow.md)

## Phase 2 Checkpoint: e7c21715

## Phase 3: Layout & Surface Negotiation (`relayout`) [checkpoint: ca9ffa52]
The core loop for window dimension negotiation and surface retrieval.

- [x] Task: Implement `relayout` and Surface retrieval. `ca9ffa52`
    - [x] **Red Phase**: Write tests verifying that `relayout` returns a valid native `Surface` handle and updated window frames.
    - [x] **Green Phase**: Implement layout calculation logic and surface handle management.
- [ ] Task: Conductor - User Manual Verification 'Phase 3: Layout & Surface' (Protocol in workflow.md)

## Phase 4: Integration & Synchronization [checkpoint: cef5c8c8]
Connect the real IPC layer to the existing view system.

- [x] Task: Implement `finishDrawing` and synchronization. `45f4f7f8`
    - [x] **Red Phase**: Write tests for the rendering sync barrier and frame completion notification.
    - [x] **Green Phase**: Implement `finishDrawing` to interface with the system compositor.
- [x] Task: Update `ViewRootImpl` to use `WindowSession`. `cef5c8c8`
    - [x] **Red Phase**: Create an integration test that triggers `perform_traversals` and asserts that real IPC calls are made.
    - [x] **Green Phase**: Replace hardcoded mocks in `ViewRootImpl.cpp` with a real `IWindowSession` instance.
- [ ] Task: Conductor - User Manual Verification 'Phase 4: Integration' (Protocol in workflow.md)

## Phase 5: Final Validation
Ensure platform compliance.

- [ ] Task: Port windowing CTS tests.
    - [ ] **Implementation**: Port foundational tests from `cts/java/android/view/cts` to verify behavioral parity.
- [ ] Task: Conductor - User Manual Verification 'Phase 5: Validation' (Protocol in workflow.md)
