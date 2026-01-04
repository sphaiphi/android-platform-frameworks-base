# SeekBar - Reverse Engineering Documentation

## Executive Summary
`SeekBar` is a standard Android widget that extends `AbsSeekBar` to provide a draggable thumb. It allows users to select a value from a continuous range (0 to max).

## Architecture Overview
*   **Inheritance**: `AbsSeekBar` -> `SeekBar`.
*   **Role**: Interactive progress bar.

## Detailed Functionality
*   **Interaction**: Adds a listener interface `OnSeekBarChangeListener` to report:
    *   `onProgressChanged`: Called when value changes (by user or code).
    *   `onStartTrackingTouch`: User touched the thumb.
    *   `onStopTrackingTouch`: User released the thumb.
*   **Accessibility**: Exposes `ACTION_SET_PROGRESS`.

## Java-to-C++ Translation Guide
*   **Events**: Implement the listener pattern (or signals).
*   **Logic**: Most logic (drawing, touch handling) is in `AbsSeekBar`. `SeekBar` is mostly just the listener API.

## Implementation Risks
*   None.
