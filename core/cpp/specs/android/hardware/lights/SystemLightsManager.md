# SystemLightsManager - Reverse Engineering Documentation

## Executive Summary
`SystemLightsManager` is the concrete implementation of `LightsManager`. It acts as a proxy to the `ILightsManager` system service (Binder interface). It handles the marshalling of requests and session management using a local `Binder` token.

## Architecture Overview
- **Pattern**: Proxy / Client Wrapper.
- **Inheritance**: Extends `LightsManager`.
- **Dependencies**: `ILightsManager` (AIDL interface).

## Detailed Functionality

### Initialization
- Connects to `Context.LIGHTS_SERVICE` ("lights") via `ServiceManager`.
- Wraps the `IBinder` result in `ILightsManager.Stub.asInterface`.

### Session Management (`SystemLightsSession`)
- **Open**: Calls `mService.openSession(token, priority)`.
- **Request**: Flattens `LightsRequest` into arrays (`int[] ids`, `LightState[] states`) and calls `mService.setLightStates`.
- **Close**: Calls `mService.closeSession(token)`.
- **Lifecycle**: Uses `CloseGuard` to warn if sessions are not closed explicitly.

### Error Handling
- Catches `RemoteException` from Binder calls and rethrows as `RuntimeException` (via `rethrowFromSystemServer()`).

## Data Model
- `mService`: `ILightsManager` (Remote proxy).

## Java-to-C++ Translation Guide

### Architecture Mapping
- **Java**: `SystemLightsManager`
- **C++**: `LightsManager` (Concrete class).

### Binder Interaction
- **Get Service**: `defaultServiceManager()->getService(String16("lights"))`.
- **Interface cast**: `interface_cast<ILightsManager>(binder)`.
- **Methods**:
  - `getLights()` -> `service->getLights(&lights)`.
  - `openSession()` -> `service->openSession(token, priority)`.

### Memory Management
- **Tokens**: C++ uses `sp<BBinder>` for the session token passed to `openSession`.
- **AutoClose**: C++ RAII (destructors) should handle `closeSession` automatically in the `LightsSession` equivalent class, eliminating the need for `CloseGuard`.

## Questions for C++ Team
- Is `rethrowFromSystemServer` logic relevant in C++? (Usually C++ returns `binder::Status` or `std::expected` and lets the caller handle it).
