# DifferentialMotionFlingHelper - Reverse Engineering Documentation

## Executive Summary
`DifferentialMotionFlingHelper` is a helper class for handling "differential motion" events (like rotary input or mouse scroll wheels) and converting them into fling gestures on a target view.

## Architecture Overview
*   **Role**: Input Processor / Physics Helper.
*   **Target**: `DifferentialMotionFlingTarget` (interface).

## Detailed Functionality
*   **Velocity Tracking**: Uses `VelocityTracker` to compute velocity from a stream of motion events.
*   **Thresholds**: Calculates fling thresholds based on `ViewConfiguration` and the specific input device.
*   **Logic**: If velocity exceeds the threshold, it triggers `target.startDifferentialMotionFling()`.

## Java-to-C++ Translation Guide
*   **Physics**: Logic is self-contained. Requires `VelocityTracker` equivalent.

## Implementation Risks
*   **Device Tuning**: Tuning the thresholds for different input devices (rotary vs mouse wheel) is critical for "feel".
