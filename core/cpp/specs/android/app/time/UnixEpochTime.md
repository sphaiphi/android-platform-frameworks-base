# UnixEpochTime - Reverse Engineering Documentation

## Executive Summary
Represents a precise point in time defined by two clocks: the Unix Epoch (wall clock) and the System Elapsed Realtime (boot clock). This duality allows the system to compute the wall clock time at any future point of elapsed realtime, compensating for processing latency.

## Architecture Overview
*   **Type**: `public final class` implementing `Parcelable`.
*   **Concept**: Reference Point (Anchor).

## Detailed Functionality
*   **Core Logic**: `at(long targetElapsedRealtime)`
    *   Calculates `TargetUnix = BaseUnix + (TargetElapsed - BaseElapsed)`.
    *   Used to project the time forward/backward.
*   **Difference**: `elapsedRealtimeDifference(a, b)` helper.

## Data Model
*   `long mElapsedRealtimeMillis`
*   `long mUnixEpochTimeMillis`

## API Reference
*   `at(long)`: Projection method.
*   `parseCommandLineArgs`: For shell tools.

## Java-to-C++ Translation Guide
*   **Math**: Simple 64-bit integer arithmetic.
*   **Types**: `int64_t`.

## Test Cases & Validation
*   `t1 = new UnixEpochTime(100, 1000)`
*   `t2 = t1.at(200)`
*   Expect `t2.unix` == 1100.

## Implementation Risks
*   Overflow: Unlikely with 64-bit millis for reasonable timeframes, but C++ `int64_t` behavior on overflow is undefined (though usually wraps). Java wraps. Check if saturation is needed (unlikely for timestamps).
