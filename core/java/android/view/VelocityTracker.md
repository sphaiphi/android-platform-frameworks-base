# VelocityTracker - Reverse Engineering Documentation

## Executive Summary
`VelocityTracker` is a high-performance utility used to calculate the speed and direction of a sequence of `MotionEvent`s. It is essential for implementing smooth "Fling" gestures in scrollable views and gesture-based navigation.

## Architecture Overview
*   **Role**: Physics-based motion analysis engine.
*   **JNI Centric**: Wraps a native C++ `VelocityTracker`.
*   **Pooling**: Uses a static `SynchronizedPool` to reuse instances and minimize allocation overhead during gestures.

## Detailed Functionality

### 1. Accumulation
*   **`addMovement()`**: Ingests `MotionEvent`s. it tracks multiple pointers independently.

### 2. Calculation
*   **`computeCurrentVelocity()`**: Solves the movement equations (typically using least-squares fitting or an impulse model) to determine the velocity in pixels per second.

### 3. Strategies
*   Supports multiple mathematical models: `IMPULSE` (default), `LSQ1`, `LSQ2`, `LEGACY`, etc., allowing for different "feels" in touch response.

## Java-to-C++ Translation Guide
*   **Native Link**: Directly wraps `android::VelocityTracker`.
*   **Math**: Relies on native polynomial fitting algorithms.

## Implementation Risks
*   **Coordinate Space**: Events added to the tracker must all be in the same coordinate system (raw or window-local). Mixing coordinate spaces will result in incorrect velocities.
*   **Stale Data**: Failure to call `clear()` between gestures will lead to "jumpy" initial velocities as old points influence the new calculation.
