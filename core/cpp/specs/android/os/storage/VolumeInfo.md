# VolumeInfo - Reverse Engineering Documentation

## Executive Summary
`VolumeInfo` represents a mountable storage entity managed by `vold`. It can be a public volume (USB/SD), a private volume (Adopted Storage), an emulated volume (Internal Storage), or a stub. It tracks the volume's lifecycle state, filesystem type, and mount points.

## Architecture Overview
-   **Pattern**: Data Object / Parcelable.
-   **Source**: `vold` via `StorageManagerService`.
-   **Relationship**: Belongs to a `DiskInfo` (optional). Can be parent to other volumes (e.g., Emulated volume on top of Private volume).

## Data Model
-   **Type** (`type`): PUBLIC, PRIVATE, EMULATED, ASEC, OBB, STUB.
-   **State** (`state`): UNMOUNTED, MOUNTED, CHECKING, EJECTING, etc.
-   **Identity**: `id` (String), `partGuid` (Partition GUID), `fsUuid` (Filesystem UUID).
-   **Mount**: `path`, `internalPath`, `mountFlags`, `mountUserId`.

## Key Methods
-   `buildStorageVolume(context, userId, ...)`: Factory method to create the user-facing `StorageVolume` object from this system info. This encapsulates the logic for path generation (`/storage/emulated/N`).
-   `isVisibleForUser(userId)`: Checks visibility based on mount flags and user association.

## Java-to-C++ Translation Guide
-   **Source of Truth**: Mirrors `android::vold::VolumeBase` hierarchy in `system/vold`.
-   **Parceling**: ID, Type, DiskInfo(Parcelable), PartGuid, MountFlags, MountUserId, State, FsType, FsUuid, FsLabel, Path, InternalPath.
