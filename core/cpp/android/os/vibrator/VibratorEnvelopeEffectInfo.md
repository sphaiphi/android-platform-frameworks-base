# VibratorEnvelopeEffectInfo - Reverse Engineering Documentation

## Executive Summary
`VibratorEnvelopeEffectInfo` describes the hardware *limitations* for playing envelope (PWLE) effects. It defines constraints like the maximum number of control points and minimum/maximum durations for segments. This helps apps/framework construct valid waveforms.

## Architecture Overview
-   **Role**: Capability Descriptor (Value Object).
-   **Fields**: `mMaxSize` (Control points), `mMinControlPointDurationMillis`, `mMaxControlPointDurationMillis`.

## API Reference
-   `getMaxSize()`: Max control points (guaranteed >= 16 if supported).
-   `getMinControlPointDurationMillis()`: Min segment duration (guaranteed <= 20ms).
-   `getMaxControlPointDurationMillis()`: Max segment duration (guaranteed >= 1000ms).
-   `getMaxDurationMillis()`: Calculated as `MaxSize * MaxSegmentDuration`.

## Java-to-C++ Translation Guide
-   **Parceling**: Simple Int, Long, Long sequence.
-   **Equivalent**: Struct in `VibratorInfo`.

## Implementation Risks
-   **Validation**: Builders should use this info to throw exceptions *before* sending invalid patterns to the HAL.
