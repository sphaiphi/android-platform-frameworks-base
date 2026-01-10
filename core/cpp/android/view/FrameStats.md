# FrameStats - Reverse Engineering Documentation

## Executive Summary
`FrameStats` is an abstract base class for collecting frame rendering statistics. it provides metadata about the refresh period and an array of timestamps for when frames were actually presented on the screen.

## Data Model
*   **`mRefreshPeriodNano`**: `long` - The theoretical time between frames in nanoseconds.
*   **`mFramesPresentedTimeNano`**: `long[]` - An array of actual presentation timestamps.

## Detailed Functionality
*   **Timing Calculation**: `getStartTimeNano()` and `getEndTimeNano()` return the total window of time covered by the statistics.
*   **Undefined Time**: Uses `UNDEFINED_TIME_NANO` (-1) to represent missing data.

## Java-to-C++ Translation Guide
*   **Mapping**: Map to a C++ `struct` or `class` named `FrameStats`.
*   **Precision**: Use `nanoseconds` as the standard unit for all timing logic.

## Implementation Risks
*   **Buffer Size**: Large frame statistic snapshots can lead to significant memory usage if not carefully managed or sampled.
