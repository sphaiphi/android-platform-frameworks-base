# ChangeText - Reverse Engineering Documentation

## Executive Summary
`ChangeText` animates text changes in `TextView`s. It supports fading out the old text and fading in the new text, or keeping the text constant.

## Data Model
-   **Properties**: Text string, selection start/end, text color.
-   **Behaviors**: `CHANGE_BEHAVIOR_KEEP`, `CHANGE_BEHAVIOR_OUT` (fade out), `CHANGE_BEHAVIOR_IN` (fade in), `CHANGE_BEHAVIOR_OUT_IN`.

## Key Algorithms
-   **`createAnimator`**:
    -   Checks if text changed.
    -   Based on behavior, sets up `ValueAnimator` to animate the alpha (via `setTextColor` ARGB manipulation).
    -   Swaps the text string inside the `AnimatorListener` (e.g., set new text when alpha reaches 0 in an OUT_IN sequence).
    -   Restores text state on pause/resume.

## Java-to-C++ Translation Guide
-   **Text Rendering**: Logic relies on changing text color alpha to simulate fade. C++ implementation might prefer layer opacity or paint alpha if available.
-   **State Management**: Crucial to swap the actual text string string content at the correct moment in the animation pipeline.
