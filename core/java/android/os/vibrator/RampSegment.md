# RampSegment - Reverse Engineering Documentation

## Executive Summary
`RampSegment` describes a linear ramp of amplitude and/or frequency. It is the fundamental building block of "Waveform" effects (often created via `VibrationEffect.createWaveform`).

## Architecture Overview
-   **Inheritance**: Extends `VibrationEffectSegment`.
-   **Legacy Context**: Used before PWLE was standardized. Often used for "HepticGenerator" or converting audio to haptics.
-   **Fields**: Start/End Amplitude, Start/End Frequency, Duration.

## Data Model
-   **Frequency 0**: Special value meaning "Resonant Frequency" (Device Default).
-   **Duration**: `int` (Note: `PwleSegment` uses `long`).

## API Reference
-   **Support**: Requires `CAP_FREQUENCY_CONTROL` if frequencies change or are non-zero. Requires `CAP_AMPLITUDE_CONTROL` if amplitudes change.
-   **Resolving**: `resolve(int)` does nothing (default amplitude not supported for ramps).

## Java-to-C++ Translation Guide
-   **Parceling**:
    -   Token: `PARCEL_TOKEN_RAMP` (4).
    -   Order: StartAmp, EndAmp, StartFreq, EndFreq, Duration (int).
-   **Handling Zero Frequency**: The C++ layer must treat `0.0f` as "Undefined/Resonant" and substitute it with the device's actual resonant frequency at runtime.

## Implementation Risks
-   **Capability Checks**: Strict checks on frequency/amplitude control capabilities are required before dispatching to hardware.
