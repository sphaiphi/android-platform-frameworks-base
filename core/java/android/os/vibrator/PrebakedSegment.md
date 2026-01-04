# PrebakedSegment - Reverse Engineering Documentation

## Executive Summary
`PrebakedSegment` represents a vibration effect that is "pre-baked" into the device hardware or ROM, identified by an integer ID (e.g., "Click", "Tick", "Thud"). It supports a "fallback" mechanism, allowing the system to substitute a different vibration if the hardware doesn't natively support the requested effect ID.

## Architecture Overview
-   **Inheritance**: Extends `VibrationEffectSegment`.
-   **Core Fields**: `mEffectId` (The ID), `mFallback` (boolean), `mEffectStrength` (Light/Medium/Strong).
-   **Use Case**: UI haptics (clicks, bumps) where consistency is preferred but hardware support varies.

## Data Model
-   **Effect IDs**: Defined in `VibrationEffect` (e.g., `EFFECT_CLICK`, `EFFECT_TICK`).
-   **Strength**: `EFFECT_STRENGTH_LIGHT`, `MEDIUM`, `STRONG`.

## Detailed Functionality
-   **Duration**: Unknown (`-1`) by default. Can be estimated via `getDuration(VibratorInfo)` by mapping effect IDs to primitive durations (e.g., `CLICK` maps to `PRIMITIVE_CLICK`).
-   **Support**: Checks `VibratorInfo.isEffectSupported`. If not supported, checks if `mFallback` is true and if the framework knows how to generate a fallback for that ID.
-   **Haptic Feedback**: Most standard prebaked effects (Click, Texture, Thud) are considered haptic feedback candidates.

## API Reference
-   `shouldFallback()`: Returns fallback status.
-   `applyEffectStrength(int)`: Returns a new segment with updated strength.

## Java-to-C++ Translation Guide
-   **Parceling**:
    -   Token: `PARCEL_TOKEN_PREBAKED` (1).
    -   Order: EffectID (int), Fallback (byte), Strength (int).
-   **Logic**: The duration estimation logic using `VibratorInfo` is key for timing calculations in C++.

## Implementation Risks
-   **Unknown Duration**: The C++ layer needs to handle `-1` duration gracefully (usually means "play until callback" or "atomic").
-   **Fallback Logic**: The decision to fallback is often complex; ensuring the C++ vibrator service respects this flag is critical.
