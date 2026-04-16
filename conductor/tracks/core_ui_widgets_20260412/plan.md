# Implementation Plan - Core UI Widgets (android.widget)

This plan outlines the steps to implement foundational UI widgets and layouts, extending the `android.view` system.

## Phase 1: Layout Foundation [checkpoint: ]
Establish the base layout parameters and the most common linear stacking container.

- [x] Task: Implement `MarginLayoutParams` in `android.view` (shared dependency). (85a0bd2)
    - [x] **Red Phase**: Write unit tests for margin calculations and property management. (85a0bd2)
    - [x] **Green Phase**: Implement `MarginLayoutParams` logic. (85a0bd2)
- [~] Task: Implement `LinearLayout` basic structure.
    - [ ] **Red Phase**: Write tests for vertical and horizontal stacking without weights.
    - [ ] **Green Phase**: Implement `LinearLayout` measure and layout passes.
- [ ] Task: Conductor - User Manual Verification 'Phase 1: Layout Foundation' (Protocol in workflow.md)

## Phase 2: Additional Layout Containers [checkpoint: ]
Implement layering and relative positioning capabilities.

- [ ] Task: Implement `FrameLayout`.
    - [ ] **Red Phase**: Write tests for Z-axis layering and gravity-based positioning.
    - [ ] **Green Phase**: Implement `FrameLayout` measurement and layout logic.
- [ ] Task: Implement `RelativeLayout` core logic.
    - [ ] **Red Phase**: Write tests for basic sibling and parent alignment rules.
    - [ ] **Green Phase**: Implement the dependency graph and two-pass layout for `RelativeLayout`.
- [ ] Task: Conductor - User Manual Verification 'Phase 2: Additional Layout Containers' (Protocol in workflow.md)

## Phase 3: Basic UI Widgets [checkpoint: ]
Implement the primary components for text display and interaction.

- [ ] Task: Implement `TextView` base widget.
    - [ ] **Red Phase**: Write tests for text property management and basic line measurement.
    - [ ] **Green Phase**: Implement `TextView` with simplified text rendering hooks.
- [ ] Task: Implement `Button` widget.
    - [ ] **Red Phase**: Write tests for click listeners and touch state management (pressed/normal).
    - [ ] **Green Phase**: Implement `Button` by extending `TextView`.
- [ ] Task: Conductor - User Manual Verification 'Phase 3: Basic UI Widgets' (Protocol in workflow.md)

## Phase 4: Advanced Layout Features [checkpoint: ]
Enhance `LinearLayout` with sophisticated distribution logic.

- [ ] Task: Implement Weight-based distribution in `LinearLayout`.
    - [ ] **Red Phase**: Write tests for proportional space distribution using `layout_weight`.
    - [ ] **Green Phase**: Update `LinearLayout` measurement pass to handle weights.
- [ ] Task: Implement Gravity support in Layouts.
    - [ ] **Red Phase**: Write tests for center, top, bottom, etc., alignment within containers.
    - [ ] **Green Phase**: Implement gravity logic in `FrameLayout` and `LinearLayout`.
- [ ] Task: Conductor - User Manual Verification 'Phase 4: Advanced Layout Features' (Protocol in workflow.md)

## Phase 5: Verification & CTS Alignment [checkpoint: ]
Final validation against Android platform standards.

- [ ] Task: Port foundational `android.widget` CTS tests.
    - [ ] Verify that measurement and layout behaviors match the Android platform exactly.
- [ ] Task: Execute comprehensive suite of framework unit tests.
    - [ ] Verify >80% code coverage for new `android.widget` components.
- [ ] Task: Conductor - User Manual Verification 'Phase 5: Verification & CTS Alignment' (Protocol in workflow.md)
