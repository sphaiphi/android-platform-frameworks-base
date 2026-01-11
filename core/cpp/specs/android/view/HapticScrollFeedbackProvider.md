# HapticScrollFeedbackProvider - Reverse Engineering Documentation

## Executive Summary
`HapticScrollFeedbackProvider` is an implementation of `ScrollFeedbackProvider` that generates tactile feedback during scrolling. It is designed to be used by individual scrolling widgets (like `ListView` or `RecyclerView`) to provide consistent "ticks" and "limit" sensations.

## Architecture Overview
*   **Role**: Haptic engine for scrollable components.
*   **Stateful**: Tracks accumulated scroll distance (`mTotalScrollPixels`) to determine when to fire a tick.
*   **Configuration**: Respects `ViewConfiguration` settings for haptic intervals and enabled states.

## Detailed Functionality

### 1. Scroll Progress
*   **`onScrollProgress()`**: Accumulates delta pixels. Once the `tickInterval` is reached, it triggers a `SCROLL_TICK` haptic effect via the view.

### 2. Edge Detection
*   **`onScrollLimit()`**: Triggers a `SCROLL_LIMIT` haptic when the user attempts to scroll past the boundaries of the content.

### 3. Item Snapping
*   **`onSnapToItem()`**: Triggers a `SCROLL_ITEM_FOCUS` haptic when a scroll gesture settles on a specific item (e.g., in a pager).

## Java-to-C++ Translation Guide
*   **Vibration Link**: Calls into `View::performHapticFeedback`.
*   **Math**: Uses simple modulo/accumulation for tick intervals.

## Implementation Risks
*   **Double Feedback**: If both the `View` class and the `Provider` instance are active, users may feel redundant vibrations. The class includes logic to disable internal view haptics when an external provider is attached.
