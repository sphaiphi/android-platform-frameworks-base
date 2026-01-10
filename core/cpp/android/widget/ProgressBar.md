# ProgressBar - Reverse Engineering Documentation

## Executive Summary
`ProgressBar` is a visual widget that indicates the progress of an operation. It supports two modes: **Determinate** (showing a specific percentage of completion) and **Indeterminate** (showing a cyclic animation for tasks of unknown duration). It heavily leverages the Android `Drawable` system for its visual representation and animation.

## Architecture Overview
*   **Inheritance**: `View` -> `ProgressBar`.
*   **Modes**:
    *   `mIndeterminate`: Boolean flag switching between cyclic animation and value-based progress.
*   **Drawables**:
    *   `mProgressDrawable`: Used for determinate mode (often a `LayerDrawable`).
    *   `mIndeterminateDrawable`: Used for indeterminate mode (often an `AnimationDrawable` or `Animatable`).
*   **Threading**: Updates to progress can be called from any thread, but the UI refresh is marshalled to the main thread via a `RefreshProgressRunnable`.

## Detailed Functionality

### 1. Progress Logic
*   **Range**: Defined by `min` and `max`.
*   **Current State**: Tracked via `mProgress` and `mSecondaryProgress`.
*   **Smooth Animation**: `setProgress(int, boolean)` uses an `ObjectAnimator` to transition the visual bar smoothly.

### 2. "Tileify" System
*   Internal logic (`tileify()`) converts standard `BitmapDrawable`s into `ClipDrawable`s with `TILE_MODE_REPEAT`. This is how Android creates the "striped" or "repeating pattern" progress bars from simple images.

### 3. Indeterminate Animation
*   If the drawable implements `Animatable`, `ProgressBar` starts it automatically.
*   Otherwise, it manually increments the drawable's "level" (0 to 10000) on every frame to drive the animation.

### 4. Tinting
*   Supports complex tinting for all layers: `progressTint`, `progressBackgroundTint`, and `secondaryProgressTint`.

## Java-to-C++ Translation Guide
*   **Level-based Drawing**: C++ implementation of the determinate bar should use a clipping mask where the width is `(progress - min) / (max - min) * totalWidth`.
*   **Animation**: Use a simple timer or integrate with `Choreographer` to update the indeterminate state.
*   **Interpolation**: Use `DecelerateInterpolator` for smooth bar growth.

## Implementation Risks
*   **Main Thread Blocking**: Frequent progress updates from background threads must be throttled to prevent flooding the main thread's message queue.
*   **Resource Management**: Custom indeterminate drawables can be memory-heavy if they use many bitmap frames.
*   **RTL**: The bar must flip its direction correctly when `mirrorForRtl` is enabled.
