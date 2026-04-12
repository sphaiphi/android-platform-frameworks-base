# Implementation Plan - Core UI Foundation (android.view)

This plan outlines the steps to implement the foundational C++ components for the `android.view` module, focusing on `View`, `ViewGroup`, `ViewRootImpl`, and `Window`.

## Phase 1: Infrastructure & IPC Integration [checkpoint: f7ede5d]
Set up the build environment and integrate the necessary AIDL interfaces for system service communication.

- [x] Task: Integrate `IWindowManager`, `IWindowSession`, `IDisplayManager`, and `IInputManager` AIDL interfaces. (6cecdbc)
    - [x] Update `core/cpp/Android.mk` to include the AIDL source files.
    - [x] Verify successful generation of C++ bindings.
- [x] Task: Implement foundational data structures for UI (e.g., `ViewConfiguration`, `DisplayInfo`). (6cecdbc)
    - [x] **Red Phase**: Write unit tests for data container integrity and serialization.
    - [x] **Green Phase**: Implement classes with modern C++23 patterns.
- [x] Task: Conductor - User Manual Verification 'Phase 1: Infrastructure & IPC Integration' (Protocol in workflow.md)

## Phase 2: Core View Hierarchy (Red/Green) [checkpoint: 396f411]
Implement the base `View` and `ViewGroup` classes with hierarchy management logic.

- [x] Task: Implement `View` base class shell. (ee6be6b)
    - [x] **Red Phase**: Define unit tests for basic view property management (visibility, ID, etc.) in `View_test.cpp`.
    - [x] **Green Phase**: Implement `View.h` and `View.cpp` according to the specification and Java baseline.
- [x] Task: Implement `ViewGroup` and hierarchy manipulation. (d578bf0)
    - [x] **Red Phase**: Write tests for adding, removing, and finding child views in `ViewGroup_test.cpp`.
    - [x] **Green Phase**: Implement `ViewGroup` logic, ensuring robust hierarchy state tracking.
- [x] Task: Implement `onMeasure` and `onLayout` mechanisms. (8abc8c9)
    - [x] **Red Phase**: Define complex nested layout tests to verify size and position propagation.
    - [x] **Green Phase**: Implement the core `measure()` and `layout()` flows in `View` and `ViewGroup`.
- [x] Task: Conductor - User Manual Verification 'Phase 2: Core View Hierarchy' (Protocol in workflow.md)

## Phase 3: Windowing & Root Integration (Red/Green) [checkpoint: 65ef251]
Implement `ViewRootImpl` and `Window` to bridge the view hierarchy with system services.

- [x] Task: Implement `Window` and `WindowCallback` abstractions. (01b4927)
    - [x] **Red Phase**: Write tests for window state management and callback distribution.
    - [x] **Green Phase**: Implement `Window.cpp` following the architectural alignment with Java.
- [x] Task: Implement `ViewRootImpl` core loop. (8c8bacd)
    - [x] **Red Phase**: Define tests for the "traversal" pass (measure -> layout -> draw).
    - [x] **Green Phase**: Implement `ViewRootImpl`, integrating with `IWindowSession` for surface acquisition.
- [x] Task: Conductor - User Manual Verification 'Phase 3: Windowing & Root Integration' (Protocol in workflow.md)

## Phase 4: Drawing & Input Integration Stubs (Red/Green) [checkpoint: 0fdd83b]
Establish the bridges for native rendering and initial event distribution.

- [x] Task: Integrate `Canvas` and `RenderNode` abstractions. (e5dda2f)
    - [x] **Red Phase**: Write unit tests for view-to-native-canvas drawing synchronization.
    - [x] **Green Phase**: Implement the `draw()` flow stubs in `View` and `ViewGroup`.
- [x] Task: Implement basic touch and focus distribution. (e5dda2f)
    - [x] **Red Phase**: Define tests for touch event bubbling and focus traversal through the hierarchy.
    - [x] **Green Phase**: Implement the initial distribution logic in `ViewGroup` and `ViewRootImpl`.
- [x] Task: Conductor - User Manual Verification 'Phase 4: Drawing & Input Integration Stubs' (Protocol in workflow.md) (0fdd83b)

## Phase 5: Verification & CTS Alignment [checkpoint: e3f8322]
Final validation of the Core UI Foundation against system standards.

- [x] Task: Execute comprehensive suite of framework unit tests. (e3f8322)
    - [x] Verify >80% code coverage for new `android.view` components.
- [x] Task: Port and run foundational `android.view` CTS tests. (e3f8322)
    - [x] Verify that measurement and layout behaviors match the Android platform exactly.
- [x] Task: Conductor - User Manual Verification 'Phase 5: Verification & CTS Alignment' (Protocol in workflow.md) (e3f8322)
