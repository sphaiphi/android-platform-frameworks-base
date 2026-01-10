# SystemUpdateManager - Reverse Engineering Documentation

## Executive Summary
`SystemUpdateManager` allows system updaters to publish the status of pending updates (e.g., "Downloading", "Install Pending"). This info is persisted across reboots via `ISystemUpdateManager` (backed by a file in `/data/system/`).

## Architecture Overview
-   **Pattern**: State Publisher / Blackboard.
-   **Service**: `ISystemUpdateManager` (Binder).
-   **Data**: `PersistableBundle` containing status keys (`KEY_STATUS`, `KEY_TITLE`, etc.).

## Data Model
-   **Status Codes**:
    -   `STATUS_IDLE` (1)
    -   `STATUS_WAITING_DOWNLOAD` (2)
    -   `STATUS_IN_PROGRESS` (3)
    -   `STATUS_WAITING_INSTALL` (4)
    -   `STATUS_WAITING_REBOOT` (5)

## API Reference
-   `retrieveSystemUpdateInfo()`: Reads the bundle.
-   `updateSystemUpdateInfo(PersistableBundle)`: Writes the bundle (requires RECOVERY permission).

## Java-to-C++ Translation Guide
-   **Binder**: Call `ISystemUpdateManager`.
-   **Persistence**: The service handles the XML file storage. The client just passes the bundle.
