# PhoneStateListener - Reverse Engineering Documentation

## Executive Summary
`PhoneStateListener` is a legacy base class used to monitor changes in telephony states (service state, signal strength, call state, etc.). While officially **deprecated** in favor of `TelephonyCallback`, it remains a core part of the Android telephony framework and is still used extensively by older applications and internal system components.

## Architecture Overview
*   **Inheritance**: `Object`.
*   **IPC Mechanism**: Implements `IPhoneStateListener.Stub` (via an internal stub class). This binder object is registered with the `TelephonyRegistry` system service.
*   **Threading**: Callbacks are executed on the `Executor` or `Handler` provided during construction.
*   **Registration**: Bound to the system via `TelephonyManager.listen(PhoneStateListener, int)`.

## Detailed Functionality

### 1. Event Subscription (Bitmask)
The listener uses a bitmask (`LISTEN_*` constants) to tell the system which events it is interested in. Key events include:
*   `LISTEN_SERVICE_STATE`: Changes in network registration.
*   `LISTEN_SIGNAL_STRENGTHS`: Detailed signal quality metrics.
*   `LISTEN_CALL_STATE`: Transition between IDLE, RINGING, and OFFHOOK.
*   `LISTEN_DATA_CONNECTION_STATE`: Packet data connection changes.

### 2. Callback Dispatch
When a telephony event occurs in the modem/radio layer:
1.  `TelephonyRegistry` (system process) receives the update.
2.  It iterates through registered listeners and calls the corresponding method on the `IPhoneStateListener` binder proxy.
3.  The client-side stub (`IPhoneStateListenerStub`) marshals the data and posts a task to the listener's `Executor`.
4.  The specific `onXXX` method (e.g., `onServiceStateChanged`) is invoked.

### 3. Permission Enforcement
Many callbacks (e.g., `onCellLocationChanged`) require sensitive permissions like `ACCESS_FINE_LOCATION`. The system process verifies these permissions before dispatching the data to the listener.

## API Reference (Partial)
*   **`LISTEN_NONE`**: Unregisters the listener.
*   **`onServiceStateChanged(ServiceState)`**: Returns the current registration state.
*   **`onCallStateChanged(int, String)`**: Reports the current call state and incoming number (requires permissions).

## Java-to-C++ Translation Guide
*   **IPC**: Implement `BnPhoneStateListener` (generated from AIDL).
*   **Data Models**: `ServiceState`, `SignalStrength`, and `CellLocation` are complex Parcelables that must be faithfully replicated in C++.
*   **Executor**: Use a thread pool or a prioritized task queue to handle the asynchronous callbacks from the telephony stack.

## Implementation Risks
*   **Memory Leaks**: Because listeners are registered with a system service, they must be explicitly unregistered (`LISTEN_NONE`) to avoid leaking the listener object and its associated Context.
*   **Stale Information**: There is a race condition between `register` and the first callback. The system usually sends the current state immediately after registration to mitigate this.
*   **Privacy**: Access to device identifiers and location info via telephony events is strictly regulated.
