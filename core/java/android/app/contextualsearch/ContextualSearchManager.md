# ContextualSearchManager - Reverse Engineering Documentation

## Executive Summary
`ContextualSearchManager` is the system service client for managing contextual search interactions. It provides methods to start the contextual search experience (either by system entrypoints or self-invocation by apps) and defines the contract (Extras, Actions) used to communicate with the contextual search activity.

## Architecture Overview
- **Pattern**: Manager / Proxy.
- **Role**: Client-side wrapper for `IContextualSearchManager`.
- **IPC**: Communicates with the system server service `contextual_search`.

## Detailed Functionality

### `startContextualSearch(@Entrypoint int entrypoint)`
**Purpose**: Initiates contextual search from a specific system entrypoint (e.g., long-press nav handle).
**Algorithm**:
1.  **Validation**: Checks if `entrypoint` is within `VALID_ENTRYPOINT_VALUES`. Throws `IllegalArgumentException` if invalid.
2.  **IPC**: Calls `mService.startContextualSearch(entrypoint)`.
3.  **Error Handling**: Rethrows `RemoteException` as runtime exception.
**Permissions**: Requires `android.permission.ACCESS_CONTEXTUAL_SEARCH`.

### `startContextualSearch()`
**Purpose**: Allows a foreground application to invoke contextual search on itself.
**Algorithm**:
1.  **IPC**: Calls `mService.startContextualSearchForForegroundApp()`.
2.  **Error Handling**: Rethrows `RemoteException`.
**Flags**: Controlled by `Flags.FLAG_SELF_INVOCATION`.

## Data Model

### Constants (Intents & Extras)
| Constant Name | Value | Purpose |
|---------------|-------|---------|
| `ACTION_LAUNCH_CONTEXTUAL_SEARCH` | `android.app.contextualsearch.action.LAUNCH_CONTEXTUAL_SEARCH` | Intent action to launch the search activity. |
| `EXTRA_ENTRYPOINT` | `...extra.ENTRYPOINT` | Integer extra indicating invocation source. |
| `EXTRA_TOKEN` | `...extra.TOKEN` | Binder token (see `CallbackToken`). |
| `EXTRA_SCREENSHOT` | `...extra.SCREENSHOT` | Bitmap/HardwareBuffer of the screen. |
| `EXTRA_VISIBLE_PACKAGE_NAMES` | `...extra.VISIBLE_PACKAGE_NAMES` | ArrayList of visible package strings. |

### Entrypoints (`@IntDef`)
Values: `ENTRYPOINT_LONG_PRESS_NAV_HANDLE` (1), `ENTRYPOINT_LONG_PRESS_HOME` (2), `ENTRYPOINT_LONG_PRESS_OVERVIEW` (3), `ENTRYPOINT_OVERVIEW_ACTION` (4), `ENTRYPOINT_OVERVIEW_MENU` (5), `ENTRYPOINT_SYSTEM_ACTION` (9), `ENTRYPOINT_LONG_PRESS_META` (10).

## API Reference

### `void startContextualSearch(int entrypoint)`
-   **Requires Permission**: `ACCESS_CONTEXTUAL_SEARCH` (Signature level).
-   **Throws**: `IllegalArgumentException` for invalid entrypoints, `RuntimeException` for IPC errors.

### `void startContextualSearch()`
-   **Security**: Caller must have a foreground activity (checked by system server).
-   **Note**: Flagged API.

## Java-to-C++ Translation Guide

| Java Concept | C++ Equivalent | Notes |
|--------------|----------------|-------|
| `IContextualSearchManager` | `sp<IContextualSearchManager>` | Generated via AIDL to C++ backend. |
| `ServiceManager.getService` | `defaultServiceManager()->getService` | |
| `Set<Integer> VALID_ENTRYPOINT_VALUES` | `std::set<int>` or `constexpr` array | Used for input validation. |
| `RemoteException.rethrowFromSystemServer` | Custom error handling | C++ methods usually return `binder::Status`. |

## Implementation Risks
-   **Service Availability**: The service might be null if the feature is disabled or system server is not ready. C++ code should handle `mService` being null or the binder call failing.
-   **Flag Dependencies**: Methods guarded by `FlaggedApi` in Java should be similarly guarded or checked in C++.

## Questions for C++ Team
-   Are the string constants defined in a shared header, or should they be duplicated in the C++ client?
