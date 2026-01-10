# SystemProperties - Reverse Engineering Documentation

## Executive Summary
`SystemProperties` provides access to the global system property store (`init` managed properties). These are key-value pairs (String -> String) used for system configuration.

## Architecture Overview
-   **Role**: Global Configuration.
-   **Native**: JNI wrappers around `libcutils` (`property_get`, `property_set`).
-   **Caching**: `Handle` class allows pre-resolving a property lookup for faster access.

## Data Model
-   **Key**: String, dot-separated (e.g., `ro.build.version.sdk`).
-   **Value**: String, max 91 characters (historically).
-   **Types**: Getters parse String into int, long, boolean.

## API Reference
-   `get(String key, String def)`
-   `getInt`, `getLong`, `getBoolean`
-   `set(String key, String val)` (Requires permission/SELinux access).
-   `addChangeCallback(Runnable)`: Notification of property changes.

## Java-to-C++ Translation Guide
-   **Equivalent**: `android-base/properties.h` (modern) or `cutils/properties.h` (legacy).
-   **Functions**:
    -   `android::base::GetProperty(key, default)`
    -   `android::base::SetProperty(key, value)`
