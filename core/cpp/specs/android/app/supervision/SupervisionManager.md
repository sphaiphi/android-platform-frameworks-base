# SupervisionManager - Reverse Engineering Documentation

## Executive Summary
`SupervisionManager` is the client-side system service wrapper for managing parental supervision on Android. It allows querying supervision state, enabling/disabling supervision, and handling related intents. It communicates with the system server via the `ISupervisionManager` AIDL interface.

## Architecture Overview
- **Pattern**: Manager / Proxy.
- **Composition**: Holds a reference to `ISupervisionManager` (the Binder proxy) and `Context`.
- **Layer**: Application Framework API.
- **Permissions**: Heavily guarded by `MANAGE_USERS`, `QUERY_USERS`, and `INTERACT_ACROSS_USERS`.

## Detailed Functionality

### `createConfirmSupervisionCredentialsIntent()`
**Purpose**: Generates an intent to launch a supervision credential confirmation screen.
**Algorithm**:
1. Checks if `mService` is connected.
2. Calls `mService.createConfirmSupervisionCredentialsIntent()`.
3. If an intent is returned, it prepares it to enter the process (security flags).
**Java-Specific Notes**:
- `RemoteException` from Binder is caught and rethrown as `RuntimeException` via `rethrowFromSystemServer()`.
- `Intent.LOCAL_FLAG_FROM_SYSTEM` is used to mark the intent as originating from the system.
**C++ Implementation Guidance**:
- Needs to call the corresponding `createConfirmSupervisionCredentialsIntent` on the `BpSupervisionManager`.
- Returned object is a parcelable `Intent` (C++ `android::content::Intent`).

### `isSupervisionEnabledForUser(int userId)`
**Purpose**: Checks if supervision is active for a specific user.
**Algorithm**:
1. Delegates to `mService.isSupervisionEnabledForUser(userId)`.
2. Handles `RemoteException`.
**C++ Implementation Guidance**:
- Direct IPC call returning a boolean.

### `setSupervisionEnabledForUser(int userId, boolean enabled)`
**Purpose**: Toggles supervision state for a user.
**Algorithm**:
1. Delegates to `mService.setSupervisionEnabledForUser(userId, enabled)`.
**C++ Implementation Guidance**:
- Direct IPC call (void return).

## Data Model

### `ISupervisionManager` (AIDL)
- **Interface**:
    - `Intent createConfirmSupervisionCredentialsIntent()`
    - `boolean isSupervisionEnabledForUser(int userId)`
    - `void setSupervisionEnabledForUser(int userId, boolean enabled)`
    - `String getActiveSupervisionAppPackage(int userId)`
    - `boolean shouldAllowBypassingSupervisionRoleQualification()`

### Constants
- `ACTION_ENABLE_SUPERVISION`: `"android.app.supervision.action.ENABLE_SUPERVISION"`
- `ACTION_DISABLE_SUPERVISION`: `"android.app.supervision.action.DISABLE_SUPERVISION"`

## API Reference

### `public Intent createConfirmSupervisionCredentialsIntent()`
- **Permissions**: `MANAGE_USERS` or `QUERY_USERS`.
- **Returns**: `Intent` or `null`.
- **Exceptions**: `RuntimeException` (wrapping RemoteException).

### `public boolean isSupervisionEnabled()`
- **Helper**: Calls `isSupervisionEnabledForUser` with current context's user ID.

### `public void setSupervisionEnabled(boolean enabled)`
- **Helper**: Calls `setSupervisionEnabledForUser` with current context's user ID.

### `public String getActiveSupervisionAppPackage()`
- **Returns**: Package name of the active supervision app or null.

### `public boolean shouldAllowBypassingSupervisionRoleQualification()`
- **Permissions**: `MANAGE_ROLE_HOLDERS`.
- **Returns**: Boolean indicating if role qualification can be bypassed.

## Java-to-C++ Translation Guide

### Binder Proxy
- **Java**: `ISupervisionManager mService`.
- **C++**: `sp<ISupervisionManager> mService`.

### Exception Handling
- **Java**: `try { ... } catch (RemoteException e) { throw e.rethrowFromSystemServer(); }`
- **C++**: Check `binder::Status` returned by methods.
    ```cpp
    binder::Status status = mService->isSupervisionEnabledForUser(userId, &result);
    if (!status.isOk()) {
        // Handle error
    }
    ```

### Context & User Handles
- **Java**: `mContext.getUserId()`.
- **C++**: Often retrieves user ID from `MultiUser` utilities or passes it explicitly.

## Test Cases & Validation
1. **Check Enabled**:
    - Input: Valid User ID.
    - Output: Boolean `true`/`false` matching system state.
2. **Set Enabled**:
    - Input: `true`.
    - Verification: Subsequent `isSupervisionEnabled` returns `true`.

## Implementation Risks
- **Null Service**: `mService` can be null (though unlikely if retrieved via system registry). Code checks for null but returns defaults (e.g., `false`, `null`), which might mask service unavailability.
- **Permissions**: C++ clients usually run as system or root, but if acting on behalf of an app, permission checks must be verified in the service implementation.
