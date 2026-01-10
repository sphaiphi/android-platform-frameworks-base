# PwleSegment - Reverse Engineering Documentation

## Executive Summary
`PwleSegment` is a segment for PWLE effects representing a transition between two absolute states (Start Amplitude/Freq -> End Amplitude/Freq) over a duration. Unlike `RampSegment` (which might imply relative behavior or legacy semantics), `PwleSegment` is strictly defined for the Normalized PWLE feature set.

## Architecture Overview
-   **Inheritance**: Extends `VibrationEffectSegment`.
-   **Key Difference from BasicPwle**: This uses explicit Frequency (Hz) rather than abstract "Sharpness".
-   **Fields**: `StartAmplitude`, `EndAmplitude`, `StartFrequencyHz`, `EndFrequencyHz`, `Duration`.

## Data Model
-   **Amplitudes**: [0, 1].
-   **Frequencies**: Hz (> 0).
-   **Duration**: ms (> 0).

## API Reference
-   **Support**: Checks if `VibratorInfo` supports envelope effects AND if the requested frequencies fall within the device's supported range (`FrequencyProfile`).
-   **Scaling**: Scales amplitudes only. Frequencies are immutable via scaling.

## Java-to-C++ Translation Guide
-   **Parceling**:
    -   Token: `PARCEL_TOKEN_PWLE` (5).
    -   Order: StartAmp, EndAmp, StartFreq, EndFreq, Duration (long).
-   **Equivalent**: `android::os::vibrator::PwleSegment`.

## Implementation Risks
-   **Frequency Support**: Apps might request frequencies the hardware cannot reproduce. The `areVibrationFeaturesSupported` check is strictly bounded by the hardware's Min/Max frequency.
-   **Flag**: Guarded by `Flags.FLAG_NORMALIZED_PWLE_EFFECTS`.
