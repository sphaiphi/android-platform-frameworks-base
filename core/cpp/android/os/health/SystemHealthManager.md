# SystemHealthManager - Reverse Engineering Documentation

## Executive Summary
`SystemHealthManager` is the primary system service API (`Context.SYSTEM_HEALTH_SERVICE`) for accessing health statistics. It exposes methods to retrieve snapshots of battery/resource usage for UIDs, and newer APIs for querying CPU/GPU "headroom" (capacity) for game optimization. It acts as a client wrapper around `IBatteryStats`, `IPowerStatsService`, and `IHintManager`.

## Architecture Overview
-   **Pattern**: System Service Wrapper.
-   **Underlying Services**:
    -   `IBatteryStats` (`batterystats`): Source of historical usage data (`UidHealthStats`).
    -   `IHintManager` (`performance_hint`): Source of real-time CPU/GPU headroom data.
    -   `IPowerStatsService` (`powerstats`): Source of Power Monitor (ODPM) readings.

## Detailed Functionality

### UID Snapshots (Legacy/Battery Stats)
-   **`takeUidSnapshot(int uid)`**: Retrieves metrics for a specific app.
    -   Checks `Flags.onewayBatteryStatsService()`.
    -   **Blocking (Legacy)**: Calls `mBatteryStats.takeUidSnapshot(uid)` which returns a `HealthStatsParceler`.
    -   **Async (Flagged)**: Uses `mBatteryStats.takeUidSnapshotsAsync` with a `SynchronousResultReceiver` to avoid blocking the main binder thread on the service side indefinitely (timeout 10s).
-   **`takeMyUidSnapshot()`**: Convenience for `Process.myUid()`.
-   **`takeUidSnapshots(int[])`**: Bulk retrieval.

### Headroom APIs (Performance Hint)
-   **Purpose**: Allow games/apps to query available CPU/GPU capacity to adjust fidelity.
-   **`getCpuHeadroom` / `getGpuHeadroom`**:
    -   Input: `CpuHeadroomParams` / `GpuHeadroomParams` (TIDs, calculation window).
    -   Validation: Checks params against limits defined in `mHintManagerClientData`.
    -   IPC: Calls `mHintManager.getCpuHeadroom(...)`.
    -   Output: Float [0.0 - 100.0] or NaN.
-   **Configuration**: `getMaxCpuHeadroomTidsSize`, `getCpuHeadroomCalculationWindowRange`, `getCpuHeadroomMinIntervalMillis`.

### Power Monitor APIs (Power Stats)
-   **`getSupportedPowerMonitors`**: Async retrieval of ODPM rails.
-   **`getPowerMonitorReadings`**: Async retrieval of energy consumption data for specific monitors.

## Data Model
-   **PendingUidSnapshots**: Helper struct for managing async snapshot requests.
-   **HintManagerClientData**: Cached configuration from `IHintManager` (supported features, ranges).

## API Reference
-   `takeUidSnapshot`: Main entry point for HealthStats.
-   `getCpuHeadroom`: Real-time CPU capacity.
-   `getGpuHeadroom`: Real-time GPU capacity.

## Java-to-C++ Translation Guide
-   This class is a high-level client. The C++ equivalent would likely be a client library interacting with the native Binder interfaces (`IBatteryStats`, `IHintManager`, `IPowerStats`).
-   **Headroom Logic**: The validation logic (checking window sizes, TID counts) should be replicated in any C++ client before making the Binder call to avoid unnecessary IPC.

## Implementation Risks
-   **Concurrency**: The `PendingUidSnapshots` logic handles concurrent requests by reusing the receiver if the UID set matches. This is a specific optimization for the Java client that might not be needed in a simpler C++ client.
-   **Flag Dependencies**: Heavily uses feature flags (`Flags.onewayBatteryStatsService`, `FLAG_CPU_GPU_HEADROOMS`). C++ implementation must respect these build-time or runtime configurations.