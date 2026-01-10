# BasicPwleSegment - Reverse Engineering Documentation

## Executive Summary
`BasicPwleSegment` is a segment of a `VibrationEffect` representing a smooth transition of intensity and sharpness over a specified duration. It is part of the PWLE (Primitive Waveform Linear Envelope) normalized effect framework, allowing abstract definitions of vibration characteristics (intensity/sharpness) mapped to the device's capabilities.

## Architecture Overview
-   **Inheritance**: Extends `VibrationEffectSegment`.
-   **Role**: Defines a "ramp" or transition in the normalized haptic space (Intensity [0,1], Sharpness [0,1]).
-   **Composition**: Used within complex `VibrationEffect` compositions to define envelope-based haptics.

## Data Model
-   **`mStartIntensity` (float)**: Initial intensity [0, 1].
-   **`mEndIntensity` (float)**: Final intensity [0, 1].
-   **`mStartSharpness` (float)**: Initial sharpness [0, 1].
-   **`mEndSharpness` (float)**: Final sharpness [0, 1].
-   **`mDuration` (long)**: Duration of the segment in milliseconds.

## API Reference
-   **Getters**: `getStartIntensity()`, `getEndIntensity()`, `getStartSharpness()`, `getEndSharpness()`, `getDuration()`.
-   **Validation**: `validate()` ensures values are within valid ranges [0, 1] and duration > 0.
-   **Scaling**: `scale()` and `scaleLinearly()` adjust intensity but preserve sharpness.
-   **Support Check**: `areVibrationFeaturesSupported()` delegates to `VibratorInfo.areEnvelopeEffectsSupported()`.

## Java-to-C++ Translation Guide
-   **C++ Equivalent**: `android::os::vibrator::BasicPwleSegment` (likely in `libvibrator` or `libvibratorinfo`).
-   **Serialization**: Implements `Parcelable`.
    -   Token: `PARCEL_TOKEN_BASIC_PWLE` (6).
    -   Write Order: StartIntensity, EndIntensity, StartSharpness, EndSharpness, Duration.
-   **Translation Strategy**: Map float fields directly. Ensure validation logic is replicated in the C++ constructor or builder.

## Implementation Risks
-   **Precision**: Ensure float precision matches between Java and C++ logic when used for waveform generation.
-   **Validation**: Invalid ranges ([0,1]) must be strictly enforced to prevent driver issues.
