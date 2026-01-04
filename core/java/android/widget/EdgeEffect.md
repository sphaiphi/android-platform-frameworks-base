# EdgeEffect - Reverse Engineering Documentation

## Executive Summary
`EdgeEffect` implements the visual overscroll effect (glow or stretch) used when a user scrolls beyond the boundaries of a scrollable view.

## Architecture Overview
*   **Role**: Visual Feedback Effect.
*   **Types**:
    *   `TYPE_GLOW`: The classic semi-circular glow.
    *   `TYPE_STRETCH`: The newer (Android 12+) effect where the content itself stretches.

## Detailed Functionality

### 1. State Machine
*   States: `IDLE`, `PULL`, `ABSORB`, `RECEDE`, `PULL_DECAY`.
*   **`onPull(deltaDistance, displacement)`**: User is actively dragging past the edge. Increases effect intensity.
*   **`onAbsorb(velocity)`**: User flung past the edge. Intensity determined by impact velocity.
*   **`onRelease()`**: User let go. Effect decays.

### 2. Rendering (`draw`)
*   **Glow**: Draws a generic "glow" drawable (or procedurally generated mesh) deformed by the pull distance. Uses a `Canvas` clip and scale.
*   **Stretch**: Uses `RenderNode.stretch()` (Hardware acceleration feature) to distort the drawing commands of the target view.

## Java-to-C++ Translation Guide
*   **Physics**: Spring physics (damped harmonic oscillator) drive the stretch effect.
*   **Shaders**: The glow is often implemented via a shader. The stretch requires specific support in the renderer (e.g., Skia or a custom vertex shader).

## Implementation Risks
*   **Renderer Support**: The stretch effect is non-trivial to implement without support from the underlying graphics engine (modifying UV coordinates or vertex positions of the view's content).
