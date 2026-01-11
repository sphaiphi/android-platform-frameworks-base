# PwlePoint - Reverse Engineering Documentation

## Executive Summary
`PwlePoint` is a data class representing a single control point in a PWLE (Primitive Waveform Linear Envelope) effect. It defines a target state (Amplitude, Frequency) and the time to reach it.

## Architecture Overview
-   **Role**: Value Object / Struct.
-   **Usage**: Used by `VibrationEffect` builders to construct PWLE waveforms. Note: This class itself is not a Segment, but a helper for defining segments (specifically `PwleSegment`).

## Data Model
-   **`mAmplitude` (float)**: Target amplitude [0, 1].
-   **`mFrequencyHz` (float)**: Target frequency (Hz).
-   **`mTimeMillis` (int)**: Duration (ms) to ramp to this point.

## API Reference
-   Getters for all fields.
-   `equals`, `hashCode`, `toString`.

## Java-to-C++ Translation Guide
-   **Equivalent**: `struct PwlePoint { float amplitude; float frequency; int duration; };`
-   **Usage**: Passed into builders or arrays in the native layer.
