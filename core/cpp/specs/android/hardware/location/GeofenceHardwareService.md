# GeofenceHardwareService - Reverse Engineering Documentation

## Executive Summary
`GeofenceHardwareService` is the Android Service component that publishes the `IGeofenceHardware` Binder interface. It delegates all logic to `GeofenceHardwareImpl`.

## Architecture Overview
- **Pattern**: Service Entry Point.
- **Inheritance**: Extends `android.app.Service`.
- **Role**: Bootstraps the implementation and handles permission checks at the entry point.

## Detailed Functionality
- **Lifecycle**: `onCreate` initializes `GeofenceHardwareImpl`.
- **Binder**: Returns `IGeofenceHardware.Stub` implementation.
- **Permission Enforcement**: Checks `LOCATION_HARDWARE` permission using `EnforcePermission` annotation and explicit checks in `GeofenceHardwareImpl`.

## Java-to-C++ Translation Guide
- **C++ Service**: This corresponds to the main service registration code (e.g., in `main.cpp` of a native service).
- **Binder Registration**: `defaultServiceManager()->addService(...)`.

## Questions for C++ Team
- None.
