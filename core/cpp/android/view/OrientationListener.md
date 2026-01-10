# OrientationListener - Reverse Engineering Documentation

## Executive Summary
`OrientationListener` is a deprecated class that provided orientation change notifications. It has been replaced by `OrientationEventListener`. Internally, this class now acts as a thin wrapper around an `OrientationEventListener` to maintain backward compatibility.

## Architecture Overview
*   **Role**: Legacy orientation observer.
*   **Implementation**: Delegates all actual sensor logic to an internal `OrientationEventListenerInternal` instance.

## Detailed Functionality
*   **`onSensorChanged()`**: (Deprecated) Receives raw values but primarily relies on the delegated `onOrientationChanged()` callback.
*   **`enable()` / `disable()`**: Proxies to the underlying listener.

## Java-to-C++ Translation Guide
*   **Recommendation**: Do NOT implement this class in a modern C++ framework. Use the `OrientationEventListener` logic directly.

## Implementation Risks
*   **Obsolete API**: This class uses the old `SensorListener` interface which is itself deprecated.
