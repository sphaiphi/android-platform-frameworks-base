# ProcessHealthStats - Reverse Engineering Documentation

## Executive Summary
`ProcessHealthStats` defines the schema for health metrics aggregated by "Process Name" (e.g., "com.android.systemui", "com.google.android.gms:unstable"). It tracks CPU usage, crash/ANR stability metrics, and foreground duration.

## Architecture Overview
-   **Role**: Key Definition Class.
-   **Context**: Used with `UidHealthStats.STATS_PROCESSES`.

## Data Model

### Metric Definitions
-   **CPU Usage**:
    -   `MEASUREMENT_USER_TIME_MS`: User-space CPU time.
    -   `MEASUREMENT_SYSTEM_TIME_MS`: Kernel-space CPU time.
-   **Stability**:
    -   `MEASUREMENT_CRASHES_COUNT`: Number of crashes.
    -   `MEASUREMENT_ANR_COUNT`: Number of Application Not Responding errors.
    -   `MEASUREMENT_STARTS_COUNT`: Number of process starts.
-   **Lifecycle**:
    -   `MEASUREMENT_FOREGROUND_MS`: Duration spent with a foreground activity.

## API Reference
-   `CONSTANTS`: Static `HealthKeys.Constants` object.

## Java-to-C++ Translation Guide
-   **Base Offset**: `BASE_PROCESS = 30000`
-   Constants 30001 to 30006.
