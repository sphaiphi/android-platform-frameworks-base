# ResourcesManager - Reverse Engineering Documentation

## Executive Summary
`ResourcesManager` is a centralized system singleton responsible for managing `Resources` and `ResourcesImpl` objects across the entire application process. It caches and reuses heavyweight objects like `AssetManager` and `ResourcesImpl` based on unique `ResourcesKey` identifiers. It handles configuration updates, multi-display support, split APKs, and the dynamic registration of shared library resource paths.

## Architecture Overview
- **Key Responsibilities**:
    - **Caching**: Maps `ResourcesKey` to `ResourcesImpl` using weak references.
    - **Token Association**: Tracks resources associated with an `Activity` or `WindowToken`.
    - **Asset Loading**: Manages `ApkAssets` and their lifecycle.
    - **Configuration Handling**: Propagates global and local configuration changes to all active `Resources` instances.
- **Core Components**:
    - `mResourceImpls`: Primary cache for implementation objects.
    - `mActivityResourceReferences`: Maps `IBinder` tokens to `ActivityResources` (which track base overrides and lists of associated resources).
    - `mCachedApkAssets`: Cache for loaded APK assets to prevent redundant I/O.
    - `mSharedLibAssetsMap`: Tracks dynamically registered library resource paths.

## Detailed Functionality

### Resource Creation (`getResources`)
**Purpose**: The main entry point for obtaining a `Resources` object.
**Algorithm**:
1. Constructs a `ResourcesKey` from the provided paths, display ID, and configuration.
2. If an `activityToken` is provided, it rebases the key's override config on top of the Activity's base override.
3. Searches for a cached `ResourcesImpl`.
4. If a miss occurs, it creates a new `AssetManager` and `ResourcesImpl`.
5. Returns a new `Resources` (or `CompatResources`) object wrapping the implementation.

### Activity Lifecycle Integration (`updateResourcesForActivity`)
**Purpose**: Syncs resources when an activity's configuration or display changes.
**Algorithm**:
1. Updates the base override configuration for the token.
2. Iterates through all `Resources` objects associated with that token.
3. Re-calculates their `ResourcesKey` and updates their `ResourcesImpl` if needed.

### Dynamic Library Registration
**Purpose**: Allows adding resource paths at runtime (e.g., for shared libraries).
**Logic**: 
- `registerResourcePaths(...)`: Adds a package's paths to `mSharedLibAssetsMap`.
- `appendLibAssetsLocked(...)`: Forces all existing `ResourcesImpl` to be recreated or updated with the new library paths.

### Memory Management
**Purpose**: Cleaning up unused references.
**Mechanism**: Uses `ReferenceQueue` and weak references for `Resources` and `ResourcesImpl`. The `cleanupReferences` method is periodically called to remove entries for garbage-collected objects.

## Data Model
- `ResourcesKey`: Immutable identifier containing all paths and configuration bits.
- `ApkKey`: Uniquely identifies an APK/ZIP file for asset loading.
- `ActivityResources`: Tracks the per-token override state.

## Java-to-C++ Translation Guide
- **Singleton**: Map to a thread-safe static singleton in C++.
- **Caching**: Use a `std::unordered_map` with `std::weak_ptr` for `ResourcesImpl`.
- **Paths**: Use `std::vector<std::string>` for asset and library paths.
- **Locking**: Use a recursive mutex or a well-defined locking order, as `ResourcesManager` is heavily synchronized.

## Implementation Risks
- **Deadlocks**: The interaction between `mLock`, `mCachedApkAssets`, and the classloader locks in `LoadedApk` can lead to deadlocks if not managed carefully.
- **I/O Overhead**: Loading `ApkAssets` is expensive. The C++ implementation must use the `ApkAssetsSupplier` pattern to minimize disk access while holding locks.
- **Complexity**: Rebasing override configurations correctly (merging parent and child overrides) is error-prone and must handle null/default values identically to the Java side.
