# IrisManager - Reverse Engineering Documentation

## Executive Summary
`IrisManager` is a system service class intended to coordinate access to iris authentication hardware. Currently, it appears to be a minimal implementation or a placeholder, primarily serving as a wrapper around the `IIrisService` Binder interface. It is marked as `@hide`, indicating it is not part of the public Android SDK API.

## Architecture Overview
- **Pattern**: Manager/Proxy pattern.
- **Role**: Client-side API surface for the Iris service.
- **Dependencies**: 
  - `android.content.Context`: For system context access.
  - `android.hardware.iris.IIrisService`: The Binder interface to the backing system service.

## Detailed Functionality

### Initialization
**Purpose**: Initializes the manager with the application context and the service interface.
**Algorithm**:
1. Accepts `Context` and `IIrisService`.
2. (Implicitly) Stores these references (though code body is empty in the provided snippet, this is the standard pattern).

**Java-Specific Notes**:
- annotated with `@SystemService(Context.IRIS_SERVICE)`, allowing retrieval via `Context.getSystemService(Context.IRIS_SERVICE)`.

## Data Model
No specific data models are defined within this class. It relies on standard Android IPC types if it were to expand.

## API Reference

### `IrisManager(Context context, IIrisService service)`
- **Visibility**: Public (but class is `@hide`).
- **Parameters**:
    - `context`: The application environment.
    - `service`: The proxy to the remote `IIrisService`.
- **Description**: Constructor for the manager.

## Java-to-C++ Translation Guide

### Architecture Mapping
In C++, interaction with system services typically bypasses the "Manager" convenience classes found in Java and interacts directly with the AIDL interfaces (Binder proxies).

- **Java**: `IrisManager` -> `IIrisService` (Proxy) -> System Server
- **C++**: `IIrisService` (BpIrisService) -> System Server

### Key Considerations
1.  **Service Retrieval**: C++ code would obtain the service via `ServiceManager::getService("iris")` (assuming "iris" is the service name registered).
2.  **Binder Interface**: The `IIrisService` would be generated from the AIDL file into C++ headers (`android/hardware/iris/IIrisService.h`).
3.  **Functionality**: Since `IrisManager.java` is empty, C++ implementation needs only to concern itself with the methods defined in `IIrisService.aidl` if it needs to perform operations.

### Dependencies
- `android::hardware::iris::IIrisService` (Generated C++ Binder interface).
- `binder/IServiceManager.h`

## Questions for C++ Team
1.  Is there a native component required for Iris authentication management, or is this strictly for upper-layer Java apps?
2.  The class is currently empty. Is functionality expected to be added, or is it deprecated/unfinished?
