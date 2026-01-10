# SupervisionManagerInternal - Reverse Engineering Documentation

## Executive Summary
`SupervisionManagerInternal` defines the local system interface for the supervision service. It is an abstract class intended to be implemented by the system server (likely the `SupervisionService` class) and exposed to other system components within the same process (LocalService). It avoids IPC overhead and exposes privileged internal operations.

## Architecture Overview
- **Type**: Abstract Base Class.
- **Pattern**: Local Service / Facade.
- **Scope**: Internal to System Server (cannot be accessed by apps).
- **Registration**: Typically registered via `LocalServices.addService(SupervisionManagerInternal.class, implementation)`.

## Detailed Functionality

### `isActiveSupervisionApp(int uid)`
**Purpose**: Verifies if a specific process UID belongs to the currently active supervision application.
**Algorithm**:
1. Determine the user associated with the `uid`.
2. Check if supervision is enabled for that user.
3. Check if the package/UID matches the designated supervision app for that user.
**Java-Specific Notes**:
- `uid` maps to a specific app identity + user identity.

### `isSupervisionEnabledForUser(int userId)`
**Purpose**: Internal accessor for supervision state.
**C++ Implementation Guidance**:
- Likely checks a persistent setting (Settings.Secure/Global) or an in-memory boolean flag managed by the service.

### `setSupervisionLockscreenEnabledForUser(...)`
**Purpose**: Controls the display of a supervision-specific lock screen.
**Parameters**:
- `userId`: Target user.
- `enabled`: Show/Hide.
- `options`: `PersistableBundle` for configuration.
**Data Structures**: `PersistableBundle` maps to `android::os::PersistableBundle` in C++.

## API Reference

### `public abstract boolean isActiveSupervisionApp(int uid)`
- **Parameters**: `uid` - Process UID.
- **Returns**: `true` if it's the active supervision app.

### `public abstract boolean isSupervisionEnabledForUser(@UserIdInt int userId)`
- **Returns**: Supervision state.

### `public abstract boolean isSupervisionLockscreenEnabledForUser(@UserIdInt int userId)`
- **Returns**: Lockscreen state.

### `public abstract void setSupervisionEnabledForUser(@UserIdInt int userId, boolean enabled)`
- **Side Effects**: Should trigger persistence and potential callbacks (like `ISupervisionAppService.onEnabled`).

### `public abstract void setSupervisionLockscreenEnabledForUser(@UserIdInt int userId, boolean enabled, @Nullable PersistableBundle options)`
- **Side Effects**: Updates Keyguard/Locksettings state.

## Java-to-C++ Translation Guide

### Abstract Class
- **Java**: `public abstract class`.
- **C++**: Pure virtual class (Interface).
    ```cpp
    class SupervisionManagerInternal {
    public:
        virtual bool isActiveSupervisionApp(uid_t uid) = 0;
        virtual bool isSupervisionEnabledForUser(userid_t userId) = 0;
        virtual void setSupervisionEnabledForUser(userid_t userId, bool enabled) = 0;
        // ...
        virtual ~SupervisionManagerInternal() = default;
    };
    ```

### Types
- **Java `int uid`** -> **C++ `uid_t`** (or `int32_t`).
- **Java `int userId`** -> **C++ `userid_t`** (or `int32_t`).
- **Java `PersistableBundle`** -> **C++ `android::os::PersistableBundle`**.

## Implementation Risks
- **Lifecycle**: This object must outlive any callers. In C++, pointer validity must be managed, usually via the `LocalServices` singleton equivalent.
- **Concurrency**: Since this is internal and potentially called from multiple system threads (ActivityManager, WindowManager), implementation must be thread-safe (locks/mutexes).
