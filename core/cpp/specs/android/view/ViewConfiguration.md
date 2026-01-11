# ViewConfiguration - Reverse Engineering Documentation

## Executive Summary
`ViewConfiguration` provides a set of standard constants and timeouts used by the UI system. It defines thresholds for touch gestures (slop, tap timeout), scrolling friction, and other device-specific UI behaviors.

## Architecture Overview
*   **Role**: Central configuration repository for UI behavior.
*   **Context-Aware**: Some values (like `touchSlop`) scale with the display density (`DisplayMetrics`).
*   **Caching**: Uses a static `sConfigurations` cache to avoid re-calculating values for every `Context`.

## Detailed Functionality

### 1. Touch Thresholds
*   **`getScaledTouchSlop()`**: Distance a touch can wander before it counts as scrolling.
*   **`getScaledPagingTouchSlop()`**: Larger threshold for paging operations (ViewPager).
*   **`getScaledDoubleTapSlop()`**: Distance tolerance for double-taps.

### 2. Timeouts
*   **`getTapTimeout()`**: Max duration for a touch to be a tap.
*   **`getLongPressTimeout()`**: Duration to trigger a long-press.
*   **`getPressedStateDuration()`**: Minimum time a view stays in "pressed" state.

### 3. Velocity
*   **`getScaledMinimumFlingVelocity()`**: Min speed to trigger a fling.
*   **`getScaledMaximumFlingVelocity()`**: Max speed clamp for flings.

## Java-to-C++ Translation Guide
*   **Access**: Should be a singleton or static accessor in the C++ UI toolkit.
*   **Density Scaling**: Ensure all pixel-based values are computed: `value_dp * density`.

## Implementation Risks
*   **Device Tuning**: Hardcoded defaults often need adjustment for specific hardware (e.g., sensitive touchscreens vs. resistive screens).
