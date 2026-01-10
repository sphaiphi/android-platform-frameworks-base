# AppGlobals - Reverse Engineering Documentation

## Executive Summary
`AppGlobals` is a static helper class providing access to global process-level state, specifically the initial `Application` object, package name, and interfaces to `PackageManager` and `PermissionManager`. It delegates directly to `ActivityThread`.

## Architecture Overview
*   **Pattern**: Static Accessor / Facade.
*   **Dependency**: `ActivityThread`.

## Detailed Functionality
*   `getInitialApplication()`: Returns `ActivityThread.currentApplication()`.
*   `getInitialPackage()`: Returns `ActivityThread.currentPackageName()`.
*   `getPackageManager()`: Returns `ActivityThread.getPackageManager()`.
*   `getPermissionManager()`: Returns `ActivityThread.getPermissionManager()`.
*   `getIntCoreSetting`/`getFloatCoreSetting`: Accesses core settings bundle from `ActivityThread`.

## Java-to-C++ Translation Guide
*   This would map to a global static accessor class in C++, likely accessing a singleton `ProcessState` or `RuntimeContext` equivalent.

## Implementation Risks
*   **Thread Safety**: Relies on `ActivityThread` being initialized.
