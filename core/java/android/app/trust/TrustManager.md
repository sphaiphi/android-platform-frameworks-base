# TrustManager - Reverse Engineering Documentation

## Executive Summary
`TrustManager` is a system service client that provides access to the Trust Management service (`TrustManagerService`). It is responsible for managing trust agents (Smart Lock), reporting unlock attempts, handling device lockout states, and notifying listeners about changes in trust state (e.g., if the device is trusted and can remain unlocked). It serves as the bridge between the application/UI layer (like Keyguard or Settings) and the core trust logic running in the system server.

## Architecture Overview
- **Pattern**: Proxy/Client wrapper around a Binder-based System Service (`ITrustManager`).
- **Communication**: Uses AIDL (`ITrustManager`, `ITrustListener`) for Inter-Process Communication (IPC) with the system server.
- **Concurrency**: Uses a `Handler` attached to the Main Looper to dispatch asynchronous callbacks to registered listeners on the main thread.
- **State Management**: Maintains a local mapping (`ArrayMap`) between client-side `TrustListener` objects and their corresponding server-side `ITrustListener` AIDL stubs.

## Detailed Functionality

### Initialization
**Purpose**: Connects to the system service.
**Algorithm**:
1.  Constructor accepts an `IBinder`.
2.  Converts `IBinder` to `ITrustManager` interface using `ITrustManager.Stub.asInterface`.
3.  Initializes an empty `ArrayMap` for listeners.
4.  Initializes a `Handler` on the Main Looper for callback dispatch.

### Listener Management (`registerTrustListener`, `unregisterTrustListener`)
**Purpose**: Allows clients to subscribe to trust state changes.
**Algorithm**:
1.  **Register**:
    -   Create a new `ITrustListener.Stub` (anonymous inner class).
    -   Implement AIDL callbacks (`onTrustChanged`, etc.) to obtain a `Message` from the local `Handler` and send it.
    -   Call `mService.registerTrustListener(stub)`.
    -   Store mapping `clientListener -> stub` in `mTrustListeners`.
2.  **Unregister**:
    -   Remove `clientListener` from `mTrustListeners`.
    -   If found, call `mService.unregisterTrustListener(stub)`.
**Java-Specific Notes**:
    -   Uses `ArrayMap` for memory efficiency.
    -   Uses anonymous inner classes for AIDL stubs.
    -   `Handler` pattern ensures callbacks run on the UI thread, crucial for UI updates.

### Reporting Events (`reportUnlockAttempt`, `reportUserRequestedUnlock`, etc.)
**Purpose**: Notifies the system server about user interactions regarding locking/unlocking.
**Algorithm**:
    -   Delegates directly to `mService`.
    -   Catches `RemoteException` and re-throws as `RuntimeException` using `rethrowFromSystemServer()`.

### Device Locking Control (`setDeviceLockedForUser`)
**Purpose**: Manually locks/unlocks a user (Managed Profiles).
**Algorithm**: Delegates to `mService.setDeviceLockedForUser`.

## Data Model

### `TrustListener` (Interface)
-   **Purpose**: Callback interface for clients.
-   **Methods**:
    -   `onTrustChanged(enabled, newlyUnlocked, userId, flags, trustGrantedMessages)`
    -   `onTrustManagedChanged(enabled, userId)`
    -   `onTrustError(message)`
    -   `onEnabledTrustAgentsChanged(userId)`
    -   `onIsActiveUnlockRunningChanged(isRunning, userId)`

### IPC Data Structures
-   **Bundle**: Used in `Handler` messages to pass complex data (flags, messages).
-   **List<String>**: For `trustGrantedMessages`.

## API Reference

### Public Methods
-   `void setDeviceLockedForUser(int userId, boolean locked)`: Sets lock state for managed profiles.
-   `void reportUnlockAttempt(boolean successful, int userId)`: Reports unlock success/failure.
-   `void reportUserRequestedUnlock(int userId, boolean dismissKeyguard)`: User indicates intent to unlock.
-   `void reportUserMayRequestUnlock(int userId)`: Hint that unlock might happen soon.
-   `void reportUnlockLockout(int timeoutMs, int userId)`: Reports device is temporarily locked out.
-   `void reportEnabledTrustAgentsChanged(int userId)`: Refreshes trust agents.
-   `void reportKeyguardShowingChanged()`: Updates keyguard visibility state.
-   `boolean isActiveUnlockRunning(int userId)`: Checks if active unlock (e.g., face unlock) is running.
-   `void registerTrustListener(TrustListener trustListener)`: Adds a listener.
-   `void unregisterTrustListener(TrustListener trustListener)`: Removes a listener.
-   `void registerDeviceLockedStateListener(IDeviceLockedStateListener listener, int deviceId)`: Listens for lock state.
-   `void unregisterDeviceLockedStateListener(IDeviceLockedStateListener listener)`: Removes lock state listener.
-   `boolean isTrustUsuallyManaged(int userId)`: Checks if trust agents are generally enabled for user.
-   `void unlockedByBiometricForUser(int userId, BiometricSourceType source)`: Reports biometric unlock.
-   `void clearAllBiometricRecognized(BiometricSourceType source, int unlockedUser)`: Clears biometric state.
-   `boolean isInSignificantPlace()`: Checks if trusted location is active.

## Java-to-C++ Translation Guide

### IPC / Binder
-   **Java**: `ITrustManager.Stub.asInterface(b)`
-   **C++**: Use `android::binder::Status` and generated AIDL C++ backends (`ITrustManager`).
-   **Exception Handling**: `RemoteException` in Java becomes `binder::Status` checks in C++.

### Listener / Callback Mechanism
-   **Java**: `Handler` + `Looper` + `Message` queue.
-   **C++**: Needs an event loop (e.g., `ALooper`) or a dedicated callback thread.
    -   The `ITrustListener` stub in C++ (`BnTrustListener`) will receive calls on a Binder thread pool.
    -   **Crucial**: You must marshal these calls to the main thread if the C++ client expects UI-thread callbacks, mimicking the Java `Handler`.

### Collections
-   **Java**: `ArrayMap<TrustListener, ITrustListener>`
-   **C++**: `std::map` or `std::unordered_map`. Since `TrustListener` is an interface pointer, keying by pointer address is standard.

### Data Types
-   **`boolean`**: `bool`
-   **`int`**: `int32_t`
-   **`List<String>`**: `std::vector<std::string>` or `std::vector<android::String16>` depending on AIDL backend.
-   **`CharSequence`**: `android::String16` or `std::string`.

## Implementation Risks
1.  **Thread Safety in Callbacks**: Java guarantees `TrustListener` methods run on the main thread via `Handler`. A naive C++ implementation might call them directly from the Binder thread pool, causing race conditions in the client.
2.  **Object Lifetimes**: Java uses GC. In C++, `sp<ITrustListener>` (strong pointer) must be managed carefully to avoid leaks or premature destruction, especially in the map.
3.  **Exception Mapping**: Ensure Binder errors are propagated or handled similar to `rethrowFromSystemServer()`.

## Questions for C++ Team
1.  Does the C++ client usage context imply a Looper is available? If not, how should callbacks be dispatched?
2.  Are we using the NDK Binder backend (stable C) or the C++ native backend?
