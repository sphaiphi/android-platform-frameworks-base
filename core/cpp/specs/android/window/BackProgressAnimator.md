# BackProgressAnimator - Reverse Engineering Documentation

## Executive Summary
`BackProgressAnimator` is a utility class that drives the visual progress of a predictive back gesture using spring physics. It smooths raw touch input into a continuous 0-1 progress value and handles the "snap back" (cancel) or "fling to finish" (invoke) animations.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `class` (Not Parcelable)
*   **Dependencies**:
    *   `com.android.internal.dynamicanimation.animation.SpringAnimation`
    *   `com.android.internal.dynamicanimation.animation.SpringForce`
    *   `com.android.internal.dynamicanimation.animation.DynamicAnimation`
*   **Role**: Logic engine for animation smoothing.

## Detailed Functionality

### Physics Model
*   **Engine**: Uses Android's `DynamicAnimation` library (Springs).
*   **Scale Factor**: Input progress (0-1) is scaled by `SCALE_FACTOR = 100f` because the physics engine works better with larger numbers. Output is divided back by 100.
*   **Forces**:
    *   `mGestureSpringForce`: `STIFFNESS_MEDIUM`, `DAMPING_RATIO_NO_BOUNCY`. Used for active gesture tracking.
    *   `mButtonSpringForce`: Used for button-triggered back events (stiffness 100).

### API & States
*   `onBackStarted(BackMotionEvent, ProgressCallback)`: Initializes the spring.
*   `onBackProgressed(BackMotionEvent)`: Updates the target position of the spring based on the event's progress.
*   `onBackCancelled(Runnable)`: Animates the spring back to 0. Invokes callback on end.
*   `onBackInvoked(Runnable)`: Animates the spring to 100% (with fling friction). Invokes callback on end.
*   `reset()`: Cancels animations and resets state.

## Java-to-C++ Translation Guide

### Algorithms
The core logic relies on a spring physics simulation.
*   **If C++ has a physics library**: Map `SpringForce` parameters (stiffness, damping) to the C++ equivalent.
*   **If no library**: A custom RK4 or Verlet integration step might be needed to simulate the spring behavior frame-by-frame.

### Key Logic
```cpp
// Pseudocode for progress update
void updateProgressValue(float value) {
    float scaledDown = value / SCALE_FACTOR;
    // Dispatch to callback
}
```

## Implementation Risks
*   **Physics Parity**: Ensuring the C++ spring feels exactly like the Java `SpringAnimation` is difficult without the exact same math implementation.
*   **Dependencies**: `DynamicAnimation` is an internal Java library.
