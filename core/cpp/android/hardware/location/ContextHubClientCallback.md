# ContextHubClientCallback - Reverse Engineering Documentation

## Executive Summary
`ContextHubClientCallback` is an abstract class defining the interface for receiving events from a Context Hub. Clients extend this class and override methods to handle messages and lifecycle events.

## Architecture Overview
- **Pattern**: Observer / Callback Interface.
- **Role**: Definition of the listener API.

## API Reference
### Methods
- `onMessageFromNanoApp(ContextHubClient, NanoAppMessage)`: Message received.
- `onHubReset(ContextHubClient)`: Hub reset detected.
- `onNanoAppAborted(...)`: Nanoapp crash/abort.
- `onNanoAppLoaded/Unloaded/Enabled/Disabled(...)`: Lifecycle events.
- `onClientAuthorizationChanged(...)`: Permission/Authorization status updates.

## Java-to-C++ Translation Guide
### Architecture Mapping
- **C++**: Pure virtual class (Interface).
  ```cpp
  class ContextHubClientCallback {
  public:
      virtual void onMessageFromNanoApp(const ContextHubClient& client, const NanoAppMessage& message) = 0;
      virtual void onHubReset(const ContextHubClient& client) = 0;
      // ... other methods
  };
  ```

## Questions for C++ Team
- None. Standard interface definition.
