# StartForegroundCalledOnStoppedServiceException - Reverse Engineering Documentation

## Executive Summary
`StartForegroundCalledOnStoppedServiceException` is a specialized exception thrown by the framework when an application attempts to call `Service.startForeground()` on a service that is either already stopped or was never successfully started. This is part of the system's enforcement of correct service lifecycle transitions.

## Architecture Overview
- **Inheritance**: Extends `IllegalStateException`.
- **Serialization**: Implements `Parcelable` for cross-process reporting.

## Detailed Functionality

### Exception Context
**Purpose**: To detect and report invalid state transitions.
**Mechanism**: Triggered by the system server during a `setServiceForeground` request if the service token is no longer valid.

### Parcelable Implementation
**Algorithm**:
- `writeToParcel`: Serializes the error message.
- `CREATOR`: Reconstructs the exception instance.

## API Reference
- `public StartForegroundCalledOnStoppedServiceException(@NonNull String message)`: Public constructor.

## Java-to-C++ Translation Guide
- **Exception Mapping**: Map to a native `android::ServiceStateException`.
- **State Validation**: C++ service management logic must track the exact operational state of each service to throw this before attempting a privileged state change.

## Implementation Risks
- **Lifecycle Races**: There is often a window between an app deciding to stop a service and the system server processing that request. C++ implementation must handle these race conditions gracefully.
