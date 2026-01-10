# TelephonyRegistryManager - Reverse Engineering Documentation

## Executive Summary
`TelephonyRegistryManager` is a hidden system service client that acts as the central hub for dispatching telephony state updates. It provides a bridge between the core telephony stack (radio, modem, IMS) and the rest of the system, including user applications. It is responsible for managing the registry of listeners and providing notification methods for state changes.

## Architecture Overview
*   **Role**: System-level Event Bus for Telephony.
*   **IPC**: Communicates with the `telephony.registry` service in the system server via `ITelephonyRegistry`.
*   **System API**: Restricted to privileged system components and carrier applications.
*   **Data Flow**: 
    1. Telephony stack components call `notifyXXX()`.
    2. `TelephonyRegistryManager` forwards the update via Binder to the system server.
    3. The system server broadcasts the update to all registered `TelephonyCallback` / `PhoneStateListener` instances.

## Detailed Functionality

### 1. Registration Management
*   Manages internal maps (`mSubscriptionChangedListenerMap`, etc.) to track active listeners.
*   **`listenFromCallback()`**: The low-level entry point for registering a modern `TelephonyCallback`.
*   **`listenFromListener()`**: The entry point for the legacy `PhoneStateListener`.

### 2. State Notification (`notifyXXX`)
Provides a massive suite of methods used by the telephony subsystem:
*   `notifyServiceStateChanged()`: Cellular registration status.
*   `notifyCallStateChanged()`: Active call transitions.
*   `notifyDataConnectionForSubscriber()`: PDN state changes.
*   `notifyEmergencyNumberList()`: Updates to localized emergency numbers.
*   `notifyDisplayInfoChanged()`: Network type icons (5G, LTE+, etc.).

### 3. Subscription Management
*   Handles listeners for SIM subscription changes and opportunistic network availability.

## Java-to-C++ Translation Guide
*   **Service Acquisition**: Use `ServiceManager::getService("telephony.registry")`.
*   **Proxy Pattern**: Implement a native `TelephonyRegistry` client that exposes the `notify` methods.
*   **Data Marshalling**: Many parameters are complex Parcelables (e.g., `PreciseDataConnectionState`). C++ must match the serialization protocol of `ITelephonyRegistry.aidl`.

## Implementation Risks
*   **High Traffic**: Telephony events (especially signal strength and cell info) can be extremely frequent. The binder traffic between the modem process and the system server must be minimized.
*   **Multi-SIM Complexity**: All methods require careful handling of `slotIndex` and `subId` to ensure data is attributed to the correct physical and logical SIM.
*   **System Reliability**: As a central dispatcher, a failure in this service will break all telephony-dependent UI (Signal bars, In-call UI, DND status).
