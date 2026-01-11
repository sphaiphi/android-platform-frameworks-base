# RestrictionsManager - Reverse Engineering Documentation

## Executive Summary
`RestrictionsManager` provides a mechanism for apps to query restrictions imposed by an administrator (DPC) or to request permissions from a restrictions provider. It proxies calls to the system service `IRestrictionsManager`.

## Architecture Overview
- **Service Name:** `Context.RESTRICTIONS_SERVICE`.
- **Relationship:** Client wrapper for `IRestrictionsManager`.

## Detailed Functionality

### `getApplicationRestrictions()`
**Purpose**: Returns the bundle of restrictions for the current package.
**Algorithm**: Calls `mService.getApplicationRestrictions(mContext.getPackageName())`.

### `requestPermission(...)`
**Purpose**: Asks the restrictions provider for a permission.
**Algorithm**: Calls `mService.requestPermission(...)`.

### `notifyPermissionResponse(...)`
**Purpose**: Called by the restrictions provider to report a result.

### `getManifestRestrictions(String packageName)`
**Purpose**: Parses the `app_restrictions` XML metadata from the manifest to return the schema of restrictions.
**Algorithm**:
1. Gets `ApplicationInfo` meta-data.
2. Loads XML resource.
3. Parses XML tags (`restriction`) into `RestrictionEntry` objects. Handles nesting.

## API Reference
- `public Bundle getApplicationRestrictions()`
- `public void requestPermission(...)`
- `public List<RestrictionEntry> getManifestRestrictions(String packageName)`

## Java-to-C++ Translation Guide
- **XML Parsing**: `getManifestRestrictions` uses `XmlResourceParser`. C++ needs an equivalent (AAPT2/ResourceTypes handling or generic XML parser if reading raw assets).
- **Binder**: Standard IPC.

## Implementation Risks
- **XML Parsing**: Robustness against malformed XML in `getManifestRestrictions`.
