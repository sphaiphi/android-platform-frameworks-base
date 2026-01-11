# RatingBar - Reverse Engineering Documentation

## Executive Summary
`RatingBar` is an `AbsSeekBar` that displays stars. It can be interactive (user taps/drags to rate) or an indicator (read-only).

## Architecture Overview
*   **Inheritance**: `AbsSeekBar` -> `RatingBar`.
*   **Role**: Star Rating.

## Detailed Functionality
*   **Drawables**: Uses a LayerDrawable (background, secondary progress, progress) where the layers are Star images. The `ProgressBar` logic handles clipping them.
*   **Step Size**: Supports fractional stars (e.g., 0.5 steps).
*   **Interaction**: `mTouchProgressOffset` is set to 0.6 to make touch selection feel more natural (rounding up).

## Java-to-C++ Translation Guide
*   **Reuse**: Heavily relies on `ProgressBar` tiling and clipping logic.

## Implementation Risks
*   None.
