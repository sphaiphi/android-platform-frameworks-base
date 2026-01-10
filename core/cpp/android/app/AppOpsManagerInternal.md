# AppOpsManagerInternal - Reverse Engineering Documentation

## Executive Summary
`AppOpsManagerInternal` is an abstract class defining the local system service interface for AppOps. It allows other system services to interact with AppOps functionality internally without going through the public AIDL interface.

## Architecture Overview
*   **Type**: Abstract Class / Service Interface.
*   **Role**: Internal API for `AppOpsService`.

## Detailed Functionality
*   **CheckOpsDelegate**: Interface to override check/note/start operations (composition pattern).
*   **Mode Management**: `setDeviceAndProfileOwners`, `setUidModeFromPermissionPolicy`, `setModeFromPermissionPolicy`.
*   **Widget Visibility**: `updateAppWidgetVisibility`.
*   **Global Restrictions**: `setGlobalRestriction`.

## Java-to-C++ Translation Guide
*   Pure virtual interface in C++.
*   Used primarily by system server components.

## Implementation Risks
*   High complexity in logic delegation (`CheckOpsDelegate`) using functional interfaces (`HexFunction`, `QuadFunction` etc.).
