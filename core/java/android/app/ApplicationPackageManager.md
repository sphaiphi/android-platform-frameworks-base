# ApplicationPackageManager - Reverse Engineering Documentation

## Executive Summary
`ApplicationPackageManager` is the concrete implementation of the `PackageManager` abstract class for the application context. It bridges the client-side API to the system's `IPackageManager` service, adding caching and context-specific logic.

## Architecture Overview
*   **Inheritance**: `PackageManager`.
*   **Dependencies**: `IPackageManager` (Binder), `ContextImpl`.

## Detailed Functionality

### Package Queries
*   `getPackageInfo`, `getApplicationInfo`: Calls `mPM.getPackageInfo` / `getApplicationInfo` with the context's User ID.
*   **Caching**: Caches `hasSystemFeature` to avoid IPC for static features.

### Resolution
*   `resolveActivity`, `queryIntentActivities`: Calls `mPM.resolveIntent` / `queryIntentActivities`.
*   Adds implicit `MATCH_` flags based on context (e.g., encryption awareness).

### Resources
*   `getResourcesForApplication`: Returns a `Resources` object for the target package.
*   `getXml`, `getDrawable`: Uses the loaded resources.

### Permissions
*   `checkPermission`: Forwards to `PermissionManager`.

## Java-to-C++ Translation Guide
*   **Binder Proxy**: Primary function is marshalling calls to `IPackageManager`.
*   **Caching**: Essential for performance (`PropertyInvalidatedCache`).

## Implementation Risks
*   **Performance**: `PackageManager` calls are very frequent. Caching layer must be robust.