# DeviceConfigInterface - Reverse Engineering Documentation

## Executive Summary
`DeviceConfigInterface` is an abstraction layer around `DeviceConfig` (Android's server-side configuration flag mechanism). It facilitates testing by allowing the injection of fake implementations.

## Architecture Overview
- **Type**: Interface.
- **Implementations**:
    -   `REAL`: Static instance that delegates directly to `DeviceConfig`.
    -   (Test implementations would implement this).

## Data Model
-   **Properties**: Namespace + Key -> Value.

## API Reference
-   `getProperty`, `getString`, `getInt`, etc.
-   `setProperty`.
-   `addOnPropertiesChangedListener`.

## Java-to-C++ Translation Guide
-   **Role**: Dependency injection interface. C++ code interacting with DeviceConfig might usually go through native APIs (`AConfig` or system properties), but if mirroring this pattern, use a virtual base class.
