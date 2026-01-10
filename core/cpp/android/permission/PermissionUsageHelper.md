# PermissionUsageHelper - Reverse Engineering Documentation

## Executive Summary
`PermissionUsageHelper` is a utility class responsible for tracking and aggregating usage of privacy-sensitive AppOps (Microphone, Camera, Location). It powers privacy indicators (the green dots/icons) and dashboards by maintaining a history of active and recent accesses.

## Architecture Overview
- **Pattern**: Observer / Helper.
- **Listeners**: Implements `AppOpsManager.OnOpActiveChangedListener` and `OnOpStartedListener`.
- **State**: Maintains in-memory maps of active attribution chains and usage history.

## Detailed Functionality

### Tracking Usage
1.  **Monitoring**: Listens to AppOp changes (`OP_CAMERA`, `OP_RECORD_AUDIO`, etc.).
2.  **Attribution Chains**: Tracks "chains" of usage (e.g., App A -> App B -> Hardware). It reconstructs these chains to properly attribute usage to the visible app or proxy.
3.  **Timings**: Distinguishes between "Running" (currently active) and "Recent" (within `RECENT_ACCESS_TIME_MS`, default 15s).

### Data Aggregation (`getOpUsageDataByDevice`)
-   Collects usage for Camera, Mic, and Location.
-   **Filtering**:
    -   Hides usage by the system package (`android`).
    -   Hides usage by exempted roles (e.g., System UI Intelligence).
    -   Hides phone call usage if a carrier-privileged app is also using the mic (deduplication).
-   **Labeling**: Resolves attribution tags (e.g., "Location for Maps") to user-friendly labels using `PackageManager`.
-   **Proxy Handling**: Identifies if an app is acting as a proxy and resolves the proxy's label.

## Data Model
-   **Ops Tracked**: `COARSE_LOCATION`, `FINE_LOCATION`, `RECORD_AUDIO`, `CAMERA`, `PHONE_CALL_*`.
-   **Structures**:
    -   `OpUsage`: Internal struct holding package, tag, op, time, and proxy info.
    -   `AccessChainLink`: Represents a node in an attribution chain.
    -   `PermissionGroupUsage`: The public output DTO.

## API Reference
-   `getOpUsageDataByDevice(...)`: Returns `List<PermissionGroupUsage>`.
-   `tearDown()`: Unregisters listeners.

## Java-to-C++ Translation Guide

### AppOp Monitoring
C++ `AppOpsManager` has similar listeners (`IAppOpsCallback`). The logic for `onOpActiveChanged` and `onOpStarted` needs to be replicated.

### Attribution Logic
The logic for reconstructing attribution chains (`mAttributionChains` map) is complex and relies on tracking `attributionChainId` and flags (`TRUSTED`, `ACCESSOR`, `RECEIVER`). This logic must be ported carefully to preserve correct blame assignment.

### Resource Loading
Resolving labels (`getLabel`, `getString`) requires access to the APK's resources. In C++, this typically involves `AssetManager`.

## Implementation Risks
-   **Race Conditions**: The class uses synchronization (`synchronized (mAttributionChains)`). C++ implementation must use equivalent locking (e.g., `std::mutex`).
-   **Memory Leaks**: Tracking chains involves dynamic allocation. Ensure chains are cleaned up when ops finish or timeout.
