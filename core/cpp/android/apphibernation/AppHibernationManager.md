# AppHibernationManager - Reverse Engineering Documentation

## Executive Summary
`AppHibernationManager` is a System API class that provides an interface for system applications to manage the hibernation state of packages. It acts as a client-side wrapper around the `IAppHibernationService` system service. It supports both user-specific hibernation (e.g., revoking permissions, force-stopping) and global hibernation (e.g., optimizing storage at the package level).

## Architecture Overview
- **Type**: System Service Wrapper (`Context.APP_HIBERNATION_SERVICE`).
- **Communication**: Uses AIDL interface `IAppHibernationService` to communicate with the system server process.
- **Pattern**: Proxy pattern. It marshals calls from the client context to the remote service.

## Detailed Functionality

### 1. User-Level Hibernation
**Purpose**: Manage whether a package is hibernating for a specific user.
**Methods**:
- `isHibernatingForUser(String packageName)`: Checks state.
- `setHibernatingForUser(String packageName, boolean isHibernating)`: Modifies state.
- `getHibernatingPackagesForUser()`: Lists all hibernating packages for the current user.
- `getHibernationStatsForUser(Set<String> packageNames)`: Retrieves storage savings stats.

### 2. Global Hibernation
**Purpose**: Manage hibernation state that affects the package across all users (Global).
**Methods**:
- `isHibernatingGlobally(String packageName)`: Checks global state.
- `setHibernatingGlobally(String packageName, boolean isHibernating)`: Modifies global state.
- `isOatArtifactDeletionEnabled()`: Checks if OAT artifact deletion is enabled as part of global hibernation.

## Data Model
- **HibernationStats**: A `Parcelable` class used to return statistics (disk space saved) about hibernating packages.

## Java-to-C++ Translation Guide
- **Binder Interface**: C++ implementation needs to interact with `IAppHibernationService` (AIDL).
- **Context**: Requires access to the Android User ID (`userId`) derived from the calling context/UID to pass to the service.
- **Error Handling**: Java catches `RemoteException` and rethrows as `RuntimeException`. C++ should handle binder status codes.

## Security
- **Permissions**: Most methods require `android.Manifest.permission.MANAGE_APP_HIBERNATION`.
