# Implementation Plan - Resource System Implementation

This plan outlines the steps to implement foundational Resource management classes in `android.content.res`.

## Phase 1: Asset Access & Management [checkpoint: bca878d]
Establish the low-level data reading infrastructure.

- [x] Task: Implement `AssetManager`. (1113a74)
    - [ ] **Red Phase**: Write unit tests for opening and reading raw files from an assets directory.
    - [ ] **Green Phase**: Implement `AssetManager` with basic file I/O using C++23 ranges/spans.
- [x] Task: Conductor - User Manual Verification 'Phase 1: Asset Access' (Protocol in workflow.md) (bca878d)

## Phase 2: Metrics & Configuration [checkpoint: ]
Define the physical and logical device properties.

- [x] Task: Implement `DisplayMetrics`. (3a96d02)
    - [ ] **Red Phase**: Write tests for density-based unit conversion math.
    - [ ] **Green Phase**: Implement `DisplayMetrics` with standard Android density constants (hdpi, xhdpi, etc.).
- [ ] Task: Implement `Configuration`.
    - [ ] **Red Phase**: Write tests for configuration matching and difference detection.
    - [ ] **Green Phase**: Implement `Configuration` with orientation and UI mode support.
- [ ] Task: Conductor - User Manual Verification 'Phase 2: Metrics & Config' (Protocol in workflow.md)

## Phase 3: Core Data Containers [checkpoint: ]
Implement the containers for resource values.

- [ ] Task: Implement `TypedValue`.
    - [ ] **Red Phase**: Write tests for data type identification and unit-aware value extraction.
    - [ ] **Green Phase**: Implement `TypedValue` using C++23 features for type safety.
- [ ] Task: Conductor - User Manual Verification 'Phase 3: Core Containers' (Protocol in workflow.md)

## Phase 4: Resource Resolution Engine [checkpoint: ]
Connect IDs to values and metrics.

- [ ] Task: Implement `Resources` class.
    - [ ] **Red Phase**: Write tests for ID-based lookup of strings and dimensions.
    - [ ] **Green Phase**: Implement `Resources` using a central mapping table and unit conversion logic.
- [ ] Task: Conductor - User Manual Verification 'Phase 4: Resolution Engine' (Protocol in workflow.md)

## Phase 5: Final Verification & Integration [checkpoint: ]
Ensure behavioral correctness against platform standards.

- [ ] Task: Port foundational `android.content.res` CTS tests.
    - [ ] Verify that dimension resolution (dp to px) matches the Android platform exactly.
- [ ] Task: Execute comprehensive suite of framework unit tests.
- [ ] Task: Conductor - User Manual Verification 'Phase 5: Verification' (Protocol in workflow.md)
