# AppWidgetManagerInternal - Reverse Engineering Documentation

## Executive Summary
`AppWidgetManagerInternal` is an abstract class defining the local system service interface for the AppWidget manager. It allows other system services (running within the same process, System Server) to interact with the AppWidget service without going through the public AIDL interface.

## Functionality

### 1. Package Management
- `getHostedWidgetPackages(int uid)`: Returns a set of package names that the specified UID is hosting. Used for permission/state checks.

### 2. User Lifecycle
- `unlockUser(int userId)`: Triggered when a user is unlocked (boot completed for user). This is likely where the service loads per-user widget data from disk or enables widgets for that user.

### 3. Resource Overlays
- `applyResourceOverlaysToWidgets(Set<String> packageNames, int userId, boolean updateFrameworkRes)`: Used by the OverlayManager to notify AppWidgetService that RROs (Runtime Resource Overlays) have changed. This forces widgets to re-inflate/update so they reflect the new resources (themes/colors).

## Java-to-C++ Translation Guide
- **Interface Definition**: This corresponds to a pure virtual class (interface) in C++.
- **Visibility**: This is internal to the system server. It does not involve IPC. It facilitates direct function calls between modules (e.g., UserManagerService -> AppWidgetService).
