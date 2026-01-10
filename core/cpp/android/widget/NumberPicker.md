# NumberPicker - Reverse Engineering Documentation

## Executive Summary
`NumberPicker` is a widget that enables the user to select a number from a predefined range. It supports two main modes: a "Spinner" mode (wheel) and an "Editable" mode (buttons + text). The default Material style uses the wheel.

## Architecture Overview
*   **Inheritance**: `LinearLayout` -> `NumberPicker`.
*   **Role**: Range Selector.
*   **Key Components**:
    *   `mInputText`: The EditText showing the current value.
    *   `mSelectorWheelPaint`: Paint for drawing the scrolling numbers.
    *   `mFlingScroller` / `mAdjustScroller`: Scrollers for physics and snapping.

## Detailed Functionality

### 1. Rendering
*   **Wheel**: Draws the current value, plus previous and next values, vertically centered. Handles wrapping (min -> max).
*   **Fading Edges**: Draws fading edges to simulate a 3D wheel effect.

### 2. Interaction
*   **Touch**: Tracks vertical drags. Uses `VelocityTracker` for flings.
*   **Snapping**: `mAdjustScroller` ensures the wheel always stops exactly on an item.
*   **Editing**: Tapping the center item focuses the `EditText`, allowing manual entry.

### 3. Formatting
*   **Formatter**: Interface to convert indices to strings (e.g., "01").
*   **DisplayedValues**: Supports arbitrary string arrays (e.g., "Mon", "Tue").

## Java-to-C++ Translation Guide
*   **Scroller**: Critical for the wheel feel.
*   **Drawing**: The wheel is drawn manually in `onDraw`. The `EditText` is a child view used for focus/editing.

## Implementation Risks
*   **Snapping**: Ensuring the wheel snaps smoothly without jitter.
*   **Input**: Switching between wheel mode and text edit mode needs careful focus management.
