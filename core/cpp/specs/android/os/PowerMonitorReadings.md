# PowerMonitorReadings - Reverse Engineering Documentation

## Executive Summary
`PowerMonitorReadings` is a container for energy measurement results returned by `IPowerStatsService`. It maps `PowerMonitor`s to energy values and timestamps.

## Architecture Overview
-   **Role**: Data Container / Result Set.
-   **Components**: Arrays of monitors, energy values, and timestamps.

## Data Model
-   `mPowerMonitors` (PowerMonitor[]): The sources.
-   `mEnergyUws` (long[]): Energy in micro-watt-seconds (microjoules).
-   `mTimestampsMs` (long[]): Timestamps.
-   `mGranularity`: Granularity level.

## Java-to-C++ Translation Guide
-   **Construction**: Constructed from parallel arrays returned by the Binder call. C++ client would receive these arrays and could wrap them similarly.
