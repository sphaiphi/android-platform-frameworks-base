# AmbientContextCallback - Reverse Engineering Documentation

## Executive Summary
This component defines the callback interface for clients interacting with the Ambient Context subsystem. It provides the mechanism for the `AmbientContextManager` to asynchronously notify applications about detected ambient events (like coughing or snoring) and the status of registration requests.

## Architecture Overview
- **Type**: Interface
- **Role**: Listener / Observer pattern component
- **Relationships**:
  - Implemented by client applications.
  - Used by `AmbientContextManager` to dispatch events and status updates.
  - Passed to `AmbientContextManager.registerObserver`.

## Detailed Functionality

### `onEvents`
**Purpose**: Delivers a list of detected ambient events to the client.
**Algorithm**:
1.  Receives a list of `AmbientContextEvent` objects.
2.  Client implementation processes this list.
**Java-Specific Notes**:
-   Uses `java.util.List` for collection.
-   Annotated with `@NonNull`.
**C++ Implementation Guidance**:
-   Should be a virtual method in a C++ abstract class.
-   `events` parameter should likely be a `const std::vector<AmbientContextEvent>&` or similar container.

### `onRegistrationComplete`
**Purpose**: Notifies the client about the success or failure of an observer registration request.
**Algorithm**:
1.  Receives an integer `statusCode`.
2.  Client implementation handles success or specific error scenarios.
**Java-Specific Notes**:
-   `statusCode` is validated against `@AmbientContextManager.StatusCode` IntDef (though effectively just an `int` at runtime).
**C++ Implementation Guidance**:
-   `statusCode` should map to a defined Enum or constant set in C++.

## Data Model
No internal state. This is a pure interface.

## API Reference

### `void onEvents(@NonNull List<AmbientContextEvent> events)`
-   **Parameters**:
    -   `events`: A non-null list of detected `AmbientContextEvent` objects.
-   **Preconditions**: `events` list is not null (though it could theoretically be empty, usually implies events occurred).
-   **Thread Safety**: Called on the `Executor` provided during registration.

### `void onRegistrationComplete(@NonNull @AmbientContextManager.StatusCode int statusCode)`
-   **Parameters**:
    -   `statusCode`: Integer representing the result of the registration (Success, Access Denied, Service Unavailable, etc.).
-   **Thread Safety**: Called on the `Executor` provided during registration.

## Java-to-C++ Translation Guide

| Java Feature | C++ Equivalent | Notes |
| :--- | :--- | :--- |
| `interface` | Abstract Class | Use pure virtual functions. |
| `List<AmbientContextEvent>` | `std::vector<AmbientContextEvent>` | Or `std::span` / custom container. |
| `int statusCode` | `enum class StatusCode : int` | Define strong types for status codes. |
| `@NonNull` | References / Smart Pointers | `const std::vector&` implies non-null. |

## Test Cases & Validation
-   **Case 1: Registration Success**: `onRegistrationComplete` called with `STATUS_SUCCESS`.
-   **Case 2: Registration Failure**: `onRegistrationComplete` called with `STATUS_ACCESS_DENIED` or `STATUS_SERVICE_UNAVAILABLE`.
-   **Case 3: Events Detected**: `onEvents` called with a list containing one `EVENT_COUGH` event.

## Implementation Risks
-   **Lifecycle Management**: In C++, ensuring the callback object remains valid while the service holds a reference to it is critical. Java handles this via GC/Binder reference counting. C++ implementation will likely need `sp<IFoo>` or `std::shared_ptr` semantics to prevent use-after-free if the registration persists longer than the callback object.

## Questions for C++ Team
-   What is the specific IPC mechanism used for callbacks in the target C++ environment (Binder, custom IPC)?
-   Are the status codes strictly aligned with the Java definitions?
