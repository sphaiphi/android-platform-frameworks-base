# ViewAnimationUtils - Reverse Engineering Documentation

## Executive Summary
`ViewAnimationUtils` provides utility methods for creating specialized view animations. its primary function is `createCircularReveal()`, which generates an `Animator` that reveals or hides a view using a circular clipping mask.

## Architecture Overview
*   **Role**: Animation factory utility.
*   **Implementation**: Returns a `RevealAnimator` (internal) which modifies the view's non-rectangular clipping properties.

## Detailed Functionality
*   **`createCircularReveal()`**: Takes a center point and a start/end radius. It is hardware-accelerated and runs asynchronously off the UI thread.

## Java-to-C++ Translation Guide
*   **Native Link**: Directly associated with `android::uirenderer::RevealAnimator`.
*   **Clipping**: Requires integration with the native rendering pipeline's circular clip operations.

## Implementation Risks
*   **Clipping Limits**: Only one non-rectangular clip can be applied at a time. A circular reveal will override standard outline clipping.
