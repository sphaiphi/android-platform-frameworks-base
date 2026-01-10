# StepSegment - Reverse Engineering Documentation

## Executive Summary
`StepSegment` represents a constant vibration at a fixed amplitude and frequency for a duration. It's an "ON" command. A sequence of StepSegments with amplitude 0 can represent "OFF" periods (gaps) in a pattern.

## Architecture Overview
-   **Inheritance**: Extends `VibrationEffectSegment`.
-   **Fields**: `mAmplitude`, `mFrequencyHz`, `mDuration`.

## Data Model
-   **Default Amplitude**: `VibrationEffect.DEFAULT_AMPLITUDE` (-1.0f). Needs `resolve()`.
-   **Frequency 0**: Default/Resonant.

## API Reference
-   **`resolve(int defaultAmplitude)`**: Maps the `-1.0f` amplitude to a normalized value `defaultAmplitude / 255.0f`.
-   **Scaling**: Scales the amplitude.

## Java-to-C++ Translation Guide
-   **Parceling**:
    -   Token: `PARCEL_TOKEN_STEP` (3).
    -   Order: Amplitude, Frequency, Duration.
-   **Optimization**: A StepSegment with `amplitude == 0` is effectively a "Wait" or "Sleep".

## Implementation Risks
-   **Unresolved Amplitude**: Attempting to play a segment with `DEFAULT_AMPLITUDE` without resolving it first will likely fail or produce undefined behavior in the HAL.
