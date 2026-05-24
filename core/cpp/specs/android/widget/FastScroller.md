# FastScroller - Reverse Engineering Documentation

## Executive Summary
`FastScroller` is a helper class used by `AbsListView` (and `RecyclerView` via similar logic) to draw and control the "fast scroll" thumb. It handles the touch logic to drag the thumb and scroll the list proportionally.

## Architecture Overview
*   **Role**: UI Controller / Overlay.
*   **Host**: `AbsListView`.
*   **Visuals**: `mThumbImage`, `mTrackImage`, `mPreviewImage` (the popup bubble showing the section letter).

## Detailed Functionality

### 1. Positioning
*   **Thumb**: Calculates vertical position based on the list's scroll position relative to the total range.
*   **Track**: Drawn behind the thumb.
*   **Preview**: Floating bubble displayed during dragging, showing the current section from `SectionIndexer`.

### 2. State Machine
*   `STATE_NONE` -> `STATE_VISIBLE` (fading in) -> `STATE_DRAGGING` (user interacting).
*   Handles auto-hiding after inactivity.

### 3. Touch Handling
*   **`onInterceptTouchEvent`**: Checks if the user touched the thumb.
*   **`onTouchEvent`**: Tracks drag movement.
*   **Math**: `currentPosition = (touchY - offset) / trackHeight`. Maps this ratio to the list adapter items/sections.

### 4. Section Indexing
*   If the adapter implements `SectionIndexer`, `FastScroller` snaps to section boundaries and displays the section text in the preview bubble.

## Java-to-C++ Translation Guide
*   **Overlay**: Implemented as a `ViewGroupOverlay` or just custom drawing on top of the list.
*   **Hit Testing**: Critical for determining when to engage fast scrolling.

## Implementation Risks
*   **List Count vs Height**: Calculating accurate scroll position in lists with variable row heights is difficult. FastScroller often approximates.
*   **RTL**: Must handle positioning on the left side for RTL locales.
