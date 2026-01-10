# AmbientContextEventRequest - Reverse Engineering Documentation

## Executive Summary
`AmbientContextEventRequest` encapsulates the criteria for initiating an ambient context detection session. It specifies *what* events to detect (a set of integer codes) and *how* to detect them (via an options bundle).

## Architecture Overview
-   **Type**: Final Data Class.
-   **Design Pattern**: Builder Pattern (`AmbientContextEventRequest.Builder`).
-   **Role**: Parameter object passed to `AmbientContextManager.registerObserver`.
-   **Dependencies**:
    -   `android.os.Parcelable`: For serialization.
    -   `java.util.Set<Integer>`: For event types.
    -   `android.os.PersistableBundle`: For configuration options.

## Detailed Functionality

### Core Logic
-   **Storage**: Stores a set of event types and an options bundle.
-   **Validation**:
    -   Event types set cannot be null or empty.
    -   Individual event types are validated against known `EventCode` definitions (via `AnnotationValidations`).
    -   Options bundle cannot be null.

## Data Model

| Field Name | Java Type | C++ Equivalent Type | Description |
| :--- | :--- | :--- | :--- |
| `mEventTypes` | `Set<Integer>` | `std::set<int32_t>` or `std::vector<int32_t>` | Collection of event IDs to monitor. |
| `mOptions` | `PersistableBundle` | `android::os::PersistableBundle` | Configuration parameters. |

## API Reference

### Getters
-   `getEventTypes()`: Returns `Set<Integer>`.
-   `getOptions()`: Returns `PersistableBundle`.

### Builder
-   `addEventType(int)`: Accumulates event types into the set.
-   `setOptions(PersistableBundle)`: Sets the configuration bundle.
-   `build()`: Constructs the request object.

## Java-to-C++ Translation Guide

### Collection Serialization
-   Java writes `Set<Integer>` to Parcel via `dest.writeArraySet`.
-   **C++ Recommendation**: When reading/writing this Parcel, iterate the container and write standard integers. Ensure the "ArraySet" header logic used by Java Parcel implementation is matched in C++ (often involves reading the size count then the elements).

### Generics/Boxing
-   Java uses `Integer` wrapper.
-   **C++ Recommendation**: Use primitive `int32_t`.

## Test Cases & Validation
-   **Empty Request**: Builder should throw exception or fail validation if `addEventType` is never called before `build()`.
-   **Serialization**: Verify set content and order (if array-backed) is preserved or irrelevant.

## Implementation Risks
-   **Empty Set Handling**: Java code explicitly throws "eventTypes cannot be empty". C++ implementation must enforce this invariant.

## Questions for C++ Team
-   None.
