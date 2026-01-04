# Switch - Reverse Engineering Documentation

## Executive Summary
`Switch` is a two-state toggle widget (on/off). It displays a track and a thumb that can be dragged or tapped. It is similar to a `ToggleButton` or `CheckBox` but with a sliding animation.

## Architecture Overview
*   **Inheritance**: `CompoundButton` -> `Switch`.
*   **Role**: Sliding Toggle.
*   **Key Components**:
    *   `mThumbDrawable`: The moving part.
    *   `mTrackDrawable`: The background.
    *   `mPositionAnimator`: Animates the thumb position.

## Detailed Functionality

### 1. Drawing
*   **Track**: Drawn first.
*   **Thumb**: Drawn on top, position offset by `mThumbPosition`.
*   **Text**: "On" or "Off" text is drawn on the track (under the thumb).
    *   `mOnLayout` / `mOffLayout`: `StaticLayout` instances for text.
    *   `mSplitTrack`: If true, clips the track to not draw under the thumb (for transparency).

### 2. Interaction
*   **Drag**: `onTouchEvent` detects drags > `mTouchSlop`. Updates `mThumbPosition` and redraws.
*   **Tap**: Toggles state and animates thumb.
*   **Animation**: `ObjectAnimator` interpolates `thumbPos` (0.0 to 1.0).

### 3. Layout
*   Calculates size based on text width, thumb width, and padding.
*   Ensures min width.

## Java-to-C++ Translation Guide
*   **Animation**: Requires property animation system.
*   **Text Layout**: `StaticLayout` equivalent needed for measuring and drawing text.
*   **Drawables**: Nine-patch support for track/thumb is standard.

## Implementation Risks
*   **RTL**: Logic for `getThumbOffset` must invert for Right-To-Left layouts.
*   **Touch Slop**: Distinguishing between a scroll (in a parent view) and a drag (on the switch) requires `requestDisallowInterceptTouchEvent`.
