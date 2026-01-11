# StorageVolume - Reverse Engineering Documentation

## Executive Summary
`StorageVolume` represents a user-specific view of a shared/external storage volume. Unlike `VolumeInfo` (which represents the physical/logical volume state in `vold`), `StorageVolume` is tailored for the application layer, containing user-specific mount paths and descriptions.

## Architecture Overview
-   **Pattern**: Data Object / Parcelable.
-   **Relationship**: derived from `VolumeInfo`.
-   **Usage**: Returned by `StorageManager.getStorageVolumes()`.

## Data Model
-   **Identity**: `mId` (String), `mUuid` (Storage UUID), `mFsUuid` (Filesystem UUID).
-   **Paths**: `mPath` (User-visible mount path), `mInternalPath` (Internal mount path).
-   **Properties**: `mDescription`, `mPrimary`, `mRemovable`, `mEmulated`.
-   **State**: `mState` (MEDIA_MOUNTED, etc.).

## API Reference
-   `getDirectory()` / `getPath()`: Access mount point.
-   `createAccessIntent()`: Legacy SAF intent builder.
-   `createOpenDocumentTreeIntent()`: Modern SAF intent builder.
-   `getMediaStoreVolumeName()`: Maps to MediaStore content URI volume name.

## Java-to-C++ Translation Guide
-   **Parceling**: Order - ID, Path, InternalPath, Desc, Primary(bool), Removable(bool), Emulated(bool), ExternallyManaged(bool), AllowMassStorage(bool), MaxFileSize(long), Owner(UserHandle), UUID(String/Int flag), FsUuid, State.
-   **Path Resolution**: The logic mapping `VolumeInfo` to `StorageVolume` paths (`/storage/emulated/0` vs `/data/media/0`) sits in `VolumeInfo.buildStorageVolume`. C++ clients usually deal with `VolumeInfo` directly.
