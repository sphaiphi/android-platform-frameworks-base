# ViewFlipper - Reverse Engineering Documentation

## Executive Summary
`ViewFlipper` is a `ViewAnimator` that adds auto-flipping capabilities (slideshow).

## Architecture Overview
*   **Inheritance**: `ViewAnimator` -> `ViewFlipper`.
*   **Difference from `AdapterViewFlipper`**: This works on direct child Views added to the layout, whereas `AdapterViewFlipper` works on an Adapter.

## Detailed Functionality
*   **Auto-Start**: Can start flipping on attach.
*   **Timer**: Uses `postDelayed` to trigger `showNext()`.

## Java-to-C++ Translation Guide
*   **Timer**: Same as `AdapterViewFlipper`.

## Implementation Risks
*   None.
