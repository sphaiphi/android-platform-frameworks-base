# PrimitiveSegment - Reverse Engineering Documentation

## Executive Summary
`PrimitiveSegment` represents a "primitive" vibration effect: a basic building block (like a "tick" or "click") that can be composed into complex patterns. These are often hardware-accelerated. The segment defines which primitive to play, a scaling factor, and a delay.

## Architecture Overview
-   **Inheritance**: Extends `VibrationEffectSegment`.
-   **Concept**: "Composition" of haptics.
-   **Fields**: `mPrimitiveId` (int), `mScale` (float), `mDelay` (int), `mDelayType` (int).

## Data Model
-   **Primitive IDs**: Constants in `VibrationEffect.Composition` (e.g., `PRIMITIVE_CLICK`, `PRIMITIVE_QUICK_RISE`).
-   **Scale**: [0, 1] float.
-   **Delay**: Milliseconds to wait *before* (or relative to, depending on type) playing.

## API Reference
-   **Validation**: Checks ID range and Scale [0,1].
-   **Duration**: `getDuration(VibratorInfo)` looks up the primitive's duration from `VibratorInfo` and adds the delay.

## Java-to-C++ Translation Guide
-   **Parceling**:
    -   Token: `PARCEL_TOKEN_PRIMITIVE` (2).
    -   Order: ID (int), Scale (float), Delay (int), DelayType (int).
-   **Equivalent**: `android::os::vibrator::PrimitiveSegment`.

## Implementation Risks
-   **Device Support**: Not all devices support all primitives. The `areVibrationFeaturesSupported` check is critical.
-   **Timing**: The `mDelay` handling in the composition logic (C++ side) needs to be precise.
