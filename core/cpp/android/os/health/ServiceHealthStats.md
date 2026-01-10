# ServiceHealthStats - Reverse Engineering Documentation

## Executive Summary
`ServiceHealthStats` defines the schema for metrics related to Android Services (`android.app.Service`). It tracks launch counts to identify restart loops or heavy service usage.

## Architecture Overview
-   **Role**: Key Definition Class.
-   **Context**: Used with `PackageHealthStats.STATS_SERVICES`.

## Data Model

### Metric Definitions
-   **`MEASUREMENT_START_SERVICE_COUNT`**: Count of `startService()` calls.
-   **`MEASUREMENT_LAUNCH_COUNT`**: Total launch count (`startService` + `bindService`).

## API Reference
-   `CONSTANTS`: Static `HealthKeys.Constants` object.

## Java-to-C++ Translation Guide
-   **Base Offset**: `BASE_SERVICE = 50000`
-   Constants 50001, 50002.
