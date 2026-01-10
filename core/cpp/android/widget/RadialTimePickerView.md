# RadialTimePickerView - Reverse Engineering Documentation

## Executive Summary
`RadialTimePickerView` is the "Clock face" UI for the Material TimePicker. It allows selecting hours and minutes by dragging a selector hand around a circle.

## Architecture Overview
*   **Inheritance**: `View` -> `RadialTimePickerView`.
*   **Role**: Custom Drawing / Input.

## Detailed Functionality

### 1. Rendering
*   **Numbers**: Draws 12 numbers (1-12 or 0-23 in two rings).
*   **Selector**: Draws a circle, a dot, and a line connecting them (the "hand").
*   **Animation**: Animates between Hour and Minute modes (`mHoursToMinutesAnimator`).

### 2. Interaction
*   **Touch**: Calculates angle from center to determine value.
    *   Maps angle to 0-11 (hours) or 0-59 (minutes).
    *   Detects distance from center to switch between inner/outer rings (24h mode).
*   **Snap**: Snaps to valid increments (e.g., minutes snap to 5-minute marks unless touch is continuous).

### 3. Accessibility
*   Uses `ExploreByTouchHelper` to expose virtual views for each number to accessibility services.

## Java-to-C++ Translation Guide
*   **Trigonometry**: Extensive use of `sin`, `cos`, `atan2` for polar coordinate conversion.
*   **Animation**: Needs a float property animator.

## Implementation Risks
*   **Touch Accuracy**: Mapping touch points to the correct number, especially in the inner ring of 24h mode.
