# UriGrantsManager - Reverse Engineering Documentation

## Executive Summary
`UriGrantsManager` is a system service responsible for managing application-level permissions to access specific `Uri`s. It allows system components (like Settings or DocumentsUI) to query or clear persistent URI permissions granted to applications. It acts as a client-side wrapper for the `IUriGrantsManager` AIDL interface.

## Architecture Overview
- **Service Integration**: Managed by `SystemServiceRegistry` and accessible via `Context.URI_GRANTS_SERVICE`.
- **Backend Communication**: Uses a singleton proxy for the `IUriGrantsManager` Binder service.
- **Security**: Access to many methods requires privileged permissions like `GET_APP_GRANTED_URI_PERMISSIONS` or `CLEAR_APP_GRANTED_URI_PERMISSIONS`.

## Detailed Functionality

### Permission Querying (`getGrantedUriPermissions`)
**Purpose**: Lists active URI grants.
**Mechanism**: Calls `mService.getGrantedUriPermissions`. It returns a `ParceledListSlice` containing `GrantedUriPermission` objects for a specific package or all packages.

### Permission Revocation (`clearGrantedUriPermissions`)
**Purpose**: Forcibly removes persistent URI access.
**Mechanism**: Calls `mService.clearGrantedUriPermissions` for a target package and user.

## API Reference
- `public static IUriGrantsManager getService()`: Internal access to the AIDL proxy.
- `public void clearGrantedUriPermissions(String packageName)`: Revocation helper.
- `public ParceledListSlice<GrantedUriPermission> getGrantedUriPermissions(...)`: Query helper.

## Java-to-C++ Translation Guide
- **AIDL Integration**: Use the AIDL-generated C++ interface `android::app::IUriGrantsManager`.
- **List Serialization**: Reimplement `ParceledListSlice` logic if needed for native list transfers.
- **Service Lookup**: Use `android::ServiceManager` to retrieve the `uri_grants` service.

## Implementation Risks
- **Privacy**: Accessing URI grants provides insight into which files or data an app can access. C++ callers must respect user privacy and enforce standard Android permission checks.
- **State Consistency**: URI grants are persistent and stored in the system server. The C++ manager is strictly a proxy and should not attempt to track its own state.
