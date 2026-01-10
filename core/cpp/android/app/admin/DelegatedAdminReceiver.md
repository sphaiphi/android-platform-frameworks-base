# DelegatedAdminReceiver - Reverse Engineering Documentation

## Executive Summary
`DelegatedAdminReceiver` is a `BroadcastReceiver` that serves as the base class for applications that have been granted delegated capabilities by a Device Owner or Profile Owner. It provides a structured way to handle system callbacks related to these delegated scopes, such as certificate selection and log retrieval. The class uses a dispatch pattern, intercepting raw broadcast intents and routing them to specific, overridable handler methods.

## Architecture Overview
This class extends `android.content.BroadcastReceiver`, making it a standard component for receiving system-wide broadcasts. Its primary architectural feature is the final `onReceive` method, which acts as a controller to dispatch incoming intents to dedicated handler methods (`onChoosePrivateKeyAlias`, `onNetworkLogsAvailable`, etc.). This enforces a clear contract for subclasses, requiring them to implement specific callbacks rather than a generic `onReceive`.

### Inheritance
- **`android.content.BroadcastReceiver`**: The fundamental base class for receiving and handling broadcast `Intent`s from the Android system.

### Design Patterns
- **Template Method Pattern**: The `onReceive` method is a final "template method" that defines the overall algorithm for handling broadcasts. It calls "hook" methods (`onChoosePrivateKeyAlias`, etc.) that subclasses must override to provide specific behavior. The default behavior of these hooks is to throw an `UnsupportedOperationException`.
- **Dispatcher**: The `onReceive` method inspects the `Intent` action and acts as a dispatcher, forwarding the request to the appropriate internal handler.

## Detailed Functionality

### `onReceive(@NonNull Context context, @NonNull Intent intent)`
**Purpose**: This is the entry point for all broadcasts sent to the receiver. It is marked as `final` and cannot be overridden.
**Algorithm**:
1. Get the action string from the incoming `Intent`.
2. Use an `if-else if` chain to check the action against known delegated admin actions (`ACTION_CHOOSE_PRIVATE_KEY_ALIAS`, `ACTION_NETWORK_LOGS_AVAILABLE`, `ACTION_SECURITY_LOGS_AVAILABLE`).
3. **For `ACTION_CHOOSE_PRIVATE_KEY_ALIAS`**:
   a. Extract `uid`, `uri`, and `alias` from the intent's extras.
   b. Call the `onChoosePrivateKeyAlias` method with the extracted data.
   c. Set the return value of `onChoosePrivateKeyAlias` as the result data of the broadcast using `setResultData()`.
4. **For `ACTION_NETWORK_LOGS_AVAILABLE`**:
   a. Extract `batchToken` and `networkLogsCount` from the intent's extras.
   b. Call the `onNetworkLogsAvailable` method.
5. **For `ACTION_SECURITY_LOGS_AVAILABLE`**:
   a. Call the `onSecurityLogsAvailable` method.
6. If the action is not recognized, log a warning.
**Java-Specific Notes**: The use of `final` prevents subclasses from breaking the dispatch logic. `setResultData()` is used for ordered broadcasts where a result is expected.

### `onChoosePrivateKeyAlias(...)`
**Purpose**: Allows a delegated app to programmatically select a private key alias for an authentication request.
**Default Behavior**: Throws `UnsupportedOperationException`.
**C++ Implementation Guidance**: This is deeply tied to the Android `KeyChain` and `Activity` model. A C++ equivalent is not directly applicable unless it's part of a full Android runtime. The core logic is about returning a string identifier based on input parameters.

### `onNetworkLogsAvailable(...)`
**Purpose**: Notifies the delegated app that a new batch of network activity logs is ready for retrieval.
**Default Behavior**: Throws `UnsupportedOperationException`.
**C++ Implementation Guidance**: This is an event-driven callback. In C++, this would be represented by a virtual function or a callback function pointer/functor that gets invoked by the event loop when network logs are available.

### `onSecurityLogsAvailable(...)`
**Purpose**: Notifies the delegated app that a new batch of security logs is ready for retrieval.
**Default Behavior**: Throws `UnsupportedOperationException`.
**C++ Implementation Guidance**: Similar to `onNetworkLogsAvailable`, this would be a virtual function or callback in a C++ system, triggered by the security logging subsystem.

## Data Model
`DelegatedAdminReceiver` is stateless. All necessary data is passed into its methods via the `Context` and `Intent` parameters.

## API Reference
- **`public final void onReceive(@NonNull Context context, @NonNull Intent intent)`**: The final entry point for broadcasts.
- **`public String onChoosePrivateKeyAlias(...)`**: Callback for handling private key alias selection. Must be overridden.
- **`public void onNetworkLogsAvailable(...)`**: Callback for when network logs are available. Must be overridden.
- **`public void onSecurityLogsAvailable(...)`**: Callback for when security logs are available. Must be overridden.

## Java-to-C++ Translation Guide
- **`BroadcastReceiver`**: The concept of a `BroadcastReceiver` maps to an event listener or observer pattern in C++. A central event bus or message queue would be responsible for dispatching events (intents) to registered listeners.
- **`Intent`**: An `Intent` is a complex message object. In C++, this would be a custom struct or class containing the action (a string or enum), and a map or variant-based structure for extras.
- **Throwing `UnsupportedOperationException`**: In C++, this can be emulated by having the base class virtual methods be pure virtual (`= 0`), forcing subclasses to implement them, or by having them throw a `std::logic_error` or a custom exception.

## Implementation Risks
- **Manifest Configuration**: A common failure point for developers using this class is forgetting to declare the receiver correctly in `AndroidManifest.xml` with the right intent filters and the `BIND_DEVICE_ADMIN` permission. While not a code risk, it's a critical part of its usage.
- **Main Thread Execution**: The Javadoc warns that callbacks run on the main thread. Developers must offload any long-running work to a background thread or a `Service` to avoid causing an Application Not Responding (ANR) error. This behavior must be clearly documented in a C++ equivalent.

## Questions for C++ Team
- What is the existing event dispatching or message bus system in the C++ environment that would be equivalent to Android's `BroadcastReceiver` mechanism?
- How should data payloads equivalent to `Intent` extras be structured and serialized for IPC in the C++ environment?
- What is the standard C++ pattern for handling required-but-unimplemented methods? Pure virtual functions or throwing exceptions from base implementations?
