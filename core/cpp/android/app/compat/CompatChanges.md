# CompatChanges - Reverse Engineering Documentation

## Executive Summary
`CompatChanges` provides the public API for checking app compatibility change states. It acts as a static utility wrapper around the `ChangeIdStateCache`, offering methods to query if specific changes are enabled for the current process, a specific package, or a UID. It also provides administrative methods to manage package overrides.

## Architecture Overview
*   **Type**: Static Utility Class.
*   **Visibility**: System API (`@SystemApi`).
*   **Core Dependency**: `ChangeIdStateCache` (Singleton instance held as `QUERY_CACHE`).

## Detailed Functionality

### 1. Querying Change Status
**Purpose**: Determine if a specific compatibility change (gate) is active.
**Variants**:
*   **Current Process**: `isChangeEnabled(long changeId)`
    *   Delegates to `Compatibility.isChangeEnabled(changeId)`.
*   **By Package**: `isChangeEnabled(long changeId, String packageName, UserHandle user)`
    *   Constructs `ChangeIdStateQuery.byPackageName`.
    *   Queries `QUERY_CACHE`.
    *   **Permissions**: Requires `READ_COMPAT_CHANGE_CONFIG` and `LOG_COMPAT_CHANGE`.
*   **By UID**: `isChangeEnabled(long changeId, int uid)`
    *   Constructs `ChangeIdStateQuery.byUid`.
    *   Queries `QUERY_CACHE`.
    *   **Permissions**: Same as above.

### 2. Managing Overrides
**Purpose**: Apply or remove manual overrides for compatibility changes (e.g., for testing or developer options).
**Mechanism**: All override methods bypass the local cache and talk directly to `IPlatformCompat` via `QUERY_CACHE.getPlatformCompatService()`.
**Permissions**: `OVERRIDE_COMPAT_CHANGE_CONFIG_ON_RELEASE_BUILD`.

**Key Operations**:
*   `putPackageOverrides`: Sets overrides for a single package.
*   `putAllPackageOverrides`: Bulk sets overrides for multiple packages (optimization).
*   `removePackageOverrides`: Removes overrides for a single package.
*   `removeAllPackageOverrides`: Bulk removes overrides.

## Data Model
Uses maps for bulk operations:
*   `Map<String, Map<Long, PackageOverride>>`
*   `Map<String, Set<Long>>`

## API Reference

### Public Static Methods
*   `boolean isChangeEnabled(long changeId)`
*   `boolean isChangeEnabled(long changeId, String packageName, UserHandle user)`
*   `boolean isChangeEnabled(long changeId, int uid)`
*   `void putPackageOverrides(String packageName, Map<Long, PackageOverride> overrides)`
*   `void putAllPackageOverrides(Map<String, Map<Long, PackageOverride>> packageNameToOverrides)`
*   `void removePackageOverrides(String packageName, Set<Long> overridesToRemove)`
*   `void removeAllPackageOverrides(Map<String, Set<Long>> packageNameToOverridesToRemove)`

## Java-to-C++ Translation Guide

### Structure
Implement as a namespace or a static class `CompatChanges`.

### Cache Integration
Ensure a single static instance of the C++ equivalent of `ChangeIdStateCache` is available to these functions.

### Permission Checks
*   **Java**: Annotations (`@RequiresPermission`) enforce checks at build time or via lint, but runtime enforcement happens in the system server.
*   **C++**: Client-side checks are generally not performed; the System Server handles security. However, if this code runs in a context that requires holding permissions, ensure the process has them.

### Data Conversion
*   **Java**: Uses `Map`, `Set`, `ArrayMap`.
*   **C++**: Use `std::map`, `std::unordered_map`, `std::set`, `std::vector`.
*   **Override Configs**:
    *   `CompatibilityOverrideConfig` and `CompatibilityOverridesByPackageConfig` are likely Parcelable classes defined in internal framework code. You will need to locate their C++ AIDL generated definitions to pass them to `IPlatformCompat`.

### Helper Functions
*   **UserHandle**: C++ code typically works with raw integer user IDs. `UserHandle.getIdentifier()` extracts this int.

## Test Cases & Validation
1.  **Self-Check**: Call `isChangeEnabled` for a known ID in the current process.
2.  **Cross-Process Check**: Call `isChangeEnabled` for a different package.
3.  **Overrides**: Apply an override, verify `isChangeEnabled` returns the overridden value, then remove it.

## Implementation Risks
*   **IPC Overhead**: Ensure `putAllPackageOverrides` is used for bulk operations to minimize Binder transactions.
*   **AIDL Availability**: The configuration classes (`CompatibilityOverrideConfig` etc.) must have C++ definitions available.
