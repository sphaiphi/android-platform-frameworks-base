# Specification - Core UI Widgets Implementation (android.widget)

## Overview
This track focuses on implementing the foundational UI widgets and layouts for the `android.widget` namespace in modern C++. This will extend the `android.view` foundation to provide developers with standard building blocks for UI construction, enabling structured layouts and basic user interaction components.

## Functional Requirements
- **Foundational Layouts**:
    - `LinearLayout`: Support for vertical and horizontal stacking of child views.
    - `FrameLayout`: Support for stacking views along the Z-axis (layering).
    - `RelativeLayout`: Support for positioning child views relative to the parent or other sibling views.
- **Basic UI Widgets**:
    - `TextView`: Core component for rendering text strings with support for basic alignment and text properties.
    - `Button`: A clickable widget extending `TextView` to handle user interaction states.
- **Advanced Layout Parameters**:
    - Implement `MarginLayoutParams` to support standard offsets.
    - `LinearLayout::LayoutParams`: Full support for `weight` based distribution, along with `gravity`.
    - Support for `match_parent` and `wrap_content` sizing logic across all new widgets and layouts.
- **Manual Instantiation**:
    - Focus on C++ API for manual view tree construction (Resource/XML loading is out of scope for this track).

## Non-Functional Requirements
- **C++23 Modernity**: Utilize modern C++ features for efficient layout calculations and state management.
- **Performance**: Ensure layout passes (measure/layout) are optimized for depth and complexity typical of these layout types.
- **API Parity**: Maintain naming and behavioral consistency with the Android Java `widget` classes.

## Acceptance Criteria
1. `LinearLayout`, `FrameLayout`, and `RelativeLayout` correctly measure and position children in nested hierarchies.
2. `TextView` successfully renders text (using internal or mock rendering bridges).
3. `Button` handles click events and state changes correctly.
4. `LinearLayout` correctly distributes space based on child weights.
5. Unit tests in `core/cpp/tests/` verify the layout logic and widget behavior.

## Out of Scope
- XML/Resource-based UI inflation (`LayoutInflater`).
- Advanced widgets like `RecyclerView`, `ListView`, or complex input fields.
- Detailed text styling (spans, custom fonts) beyond basic properties.
- Image rendering (`ImageView`).
