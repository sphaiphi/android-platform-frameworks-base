# PidHealthStats - Reverse Engineering Documentation

## Executive Summary
`PidHealthStats` defines the schema for "live" health metrics associated with a specific Process ID (PID). Unlike other aggregated stats, these represent the current state of a running process, useful for debugging active resource leaks (specifically WakeLocks).

## Architecture Overview
-   **Role**: Key Definition Class.
-   **Context**: Used with `UidHealthStats.STATS_PIDS`.
-   **Focus**: WakeLock debugging.

## Data Model

### Metric Definitions
-   **`MEASUREMENT_WAKE_NESTING_COUNT`** (Type: `MEASUREMENT`): Current depth of nested wakelocks (Acquired - Released). Non-zero implies active holding.
-   **`MEASUREMENT_WAKE_SUM_MS`** (Type: `MEASUREMENT`): Total duration (ms) this PID has held wakelocks.
-   **`MEASUREMENT_WAKE_START_MS`** (Type: `MEASUREMENT`): Timestamp (ElapsedRealtime) when the *first* currently active wakelock was acquired. Used to determine how long the device has been kept awake continuously by this PID.

## API Reference
-   `CONSTANTS`: Static `HealthKeys.Constants` object.

## Java-to-C++ Translation Guide
-   **Base Offset**: `BASE_PID = 20000`
-   `MEASUREMENT_WAKE_NESTING_COUNT = 20001`
-   `MEASUREMENT_WAKE_SUM_MS = 20002`
-   `MEASUREMENT_WAKE_START_MS = 20003`
