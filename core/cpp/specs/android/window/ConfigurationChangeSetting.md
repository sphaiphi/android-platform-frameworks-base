# ConfigurationChangeSetting - Reverse Engineering Documentation

## Executive Summary
`ConfigurationChangeSetting` is an abstract Parcelable class acting as a base for specific configuration change requests (like density or font scale) that can be applied transactionally (in a batch). This avoids multiple configuration updates and re-layouts.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `abstract class` implements `Parcelable`
*   **Subclasses**:
    *   `DensitySetting`: Changing display density.
    *   `FontScaleSetting`: Changing font scale.
*   **Inner Interface**: `ConfigurationChangeSettingInternal` (Server-side factory).

## Data Model

### Base Class
*   `mSettingType`: `int` (0 for Density, 1 for FontScale).

### DensitySetting
*   `mDisplayId`: `int`.
*   `mDensity`: `int` (DPI).

### FontScaleSetting
*   `mFontScaleFactor`: `float`.

## Detailed Functionality

### Creation (`CreatorImpl`)
**Mechanism**:
*   The `CREATOR` handles polymorphism during unparceling.
*   It reads the `settingType` int first.
*   **Client vs System**:
    *   If `ActivityThread.isSystem()` is true, it delegates to `ConfigurationChangeSettingInternal` via `LocalServices`. This suggests the system server has a specialized implementation/factory that isn't present in the client jar or requires dependency injection.
    *   If client, it directly creates `DensitySetting` or `FontScaleSetting`.

### `apply(@UserIdInt int userId)`
*   Abstract-ish concept (base implementation is no-op in client).
*   Intended to be executed on the server side to actually modify the system settings.

## Java-to-C++ Translation Guide

### Polymorphism
*   Use a base `struct` or `class` with a `virtual` destructor.
*   `Parcelable` implementation in C++ needs to handle reading the type tag and then creating the correct subclass instance.

### System Server Dependency
*   The Java code relies on `LocalServices` for system-process-specific logic. In C++, if this code runs in the system server, it will need access to the equivalent service registry or factory. If it runs in the client, it just deserializes data.

### Parceling
*   **Base**: Write `mSettingType`.
*   **DensitySetting**: Write Base, then `mDisplayId`, `mDensity`.
*   **FontScaleSetting**: Write Base, then `mFontScaleFactor`.

## Implementation Risks
*   **Flag Dependency**: The constructor throws if `Flags.condenseConfigurationChangeForSimpleMode()` is not enabled. C++ code should likely check this AConfig flag as well.
