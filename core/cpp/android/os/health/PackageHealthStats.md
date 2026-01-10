# PackageHealthStats - Reverse Engineering Documentation

## Executive Summary
`PackageHealthStats` defines the schema (keys) for health metrics aggregated at the Android Package (APK) level. It contains constants for accessing nested service statistics and wakeup alarm counts.

## Architecture Overview
-   **Role**: Key Definition Class.
-   **Context**: Used with `UidHealthStats.STATS_PACKAGES`.
-   **Annotation**: Uses `@HealthKeys.Constant` to define key types.

## Data Model

### Metric Definitions
-   **`STATS_SERVICES`** (Type: `STATS`): Map of Service Names -> `ServiceHealthStats`. Tracks health data for individual services defined within the package.
-   **`MEASUREMENTS_WAKEUP_ALARMS_COUNT`** (Type: `MEASUREMENTS`): Map of Alarm Tags -> `Long` (Count). Tracks how many times specific alarms (identified by tag) woke up the device.

## API Reference
-   `CONSTANTS`: Static `HealthKeys.Constants` object initialized for this class. Used by `HealthStatsWriter` to build indices.

## Java-to-C++ Translation Guide
-   Define these integer constants in a C++ header or enum.
-   Ensure the base offset (`BASE_PACKAGE = 40000`) matches.
-   `STATS_SERVICES = 40001`
-   `MEASUREMENTS_WAKEUP_ALARMS_COUNT = 40002`
