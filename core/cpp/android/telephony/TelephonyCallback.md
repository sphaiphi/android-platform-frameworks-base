# TelephonyCallback - Reverse Engineering Documentation

## Executive Summary
`TelephonyCallback` is the modern, interface-based replacement for the deprecated `PhoneStateListener`. It allows applications to selectively monitor specific telephony events by implementing one or more sub-interfaces. This design provides better type safety and efficiency by only delivering requested data types.

## Architecture Overview
*   **Design Pattern**: Observer Pattern with granular interfaces.
*   **Composition**: A single `TelephonyCallback` instance can implement multiple listeners (e.g., `ServiceStateListener`, `SignalStrengthsListener`).
*   **Registration**: Handled via `TelephonyManager.registerTelephonyCallback(Executor, TelephonyCallback)`.
*   **Internal Linkage**: Uses the same underlying `IPhoneStateListener` binder protocol as the legacy system, ensuring backward compatibility at the IPC level.

## Detailed Functionality

### 1. Granular Interfaces
Users implement specific interfaces corresponding to telephony events:
*   `TelephonyCallback.ServiceStateListener`
*   `TelephonyCallback.CallStateListener`
*   `TelephonyCallback.CellInfoListener`
*   `TelephonyCallback.DataActivityListener`

### 2. Event Filtering
Instead of a bitmask, the `TelephonyManager` inspects which interfaces the provided object implements and registers only for those specific `EVENT_*` codes with the `TelephonyRegistry`.

### 3. Resource Limits
To prevent system abuse, there is a per-process limit on the number of registered callbacks (default: 50). This is enforced via `PHONE_STATE_LISTENER_LIMIT_CHANGE_ID`.

## API Reference

### Key Sub-Interfaces
*   **`ServiceStateListener`**: `onServiceStateChanged(ServiceState)`
*   **`SignalStrengthsListener`**: `onSignalStrengthsChanged(SignalStrength)`
*   **`MessageWaitingIndicatorListener`**: `onMessageWaitingIndicatorChanged(boolean)`

## Java-to-C++ Translation Guide
*   **Polymorphism**: In C++, use multiple inheritance from abstract listener classes to mirror the Java interface structure.
*   **Registration**: Create a manager class that keeps a map of implemented event IDs to callback functions.
*   **Thread Safety**: Since callbacks are executed on a provided `Executor`, the C++ equivalent should use a `std::function` or a similar delegate mechanism executed on a worker thread.

## Implementation Risks
*   **Reference Management**: `TelephonyCallback` is often held as a `WeakReference` internally by the registry proxy. C++ implementation must ensure the lifecycle of the listener is clear to the caller.
*   **Permission Checks**: The implementation should handle `SecurityException` gracefully if the caller lacks the necessary location or phone state permissions for a specific interface.
