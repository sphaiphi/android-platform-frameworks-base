# GpsBatteryStats - Reverse Engineering Documentation

## Executive Summary
`GpsBatteryStats` is a Parcelable class for encapsulating power consumption statistics related to the GPS/GNSS receiver. It tracks the duration of usage, energy consumed, and time spent at different signal quality levels.

## Architecture Overview
-   **Type**: Data Object / Parcelable.
-   **Usage**: Internal/Hidden API (`@hide`), likely used for reporting GNSS power stats to `BatteryStats`.

## Data Model
-   `mLoggingDurationMs` (long): Total time duration of the stats.
-   `mEnergyConsumedMaMs` (long): Energy consumed in milli-ampere milliseconds.
-   `mTimeInGpsSignalQualityLevel` (long[]): Array tracking time spent in different signal quality levels.

## API Reference
-   **Setters**: `setLoggingDurationMs`, `setEnergyConsumedMaMs`, `setTimeInGpsSignalQualityLevel`.
-   **Getters**: Corresponding accessors.
-   **Parceling**: Standard read/write methods.

## Java-to-C++ Translation Guide
-   **Parceling Order**:
    1.  `mLoggingDurationMs` (Long)
    2.  `mEnergyConsumedMaMs` (Long)
    3.  `mTimeInGpsSignalQualityLevel` (Long Array)
-   **Array Size**: `mTimeInGpsSignalQualityLevel` is capped at `GnssSignalQuality.NUM_GNSS_SIGNAL_QUALITY_LEVELS` (typically 2: Low/High quality).

## Implementation Risks
-   **Initialization**: The default constructor initializes fields to 0 and allocates the array. C++ should ensure similar initialization safety.