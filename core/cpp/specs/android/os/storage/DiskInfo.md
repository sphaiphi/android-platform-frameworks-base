# DiskInfo - Reverse Engineering Documentation

## Executive Summary
`DiskInfo` represents a physical storage device (e.g., SD card, USB drive) connected to the system. It contains metadata like disk ID, size, labels, and flags indicating its capabilities (adoptable, SD, USB). It serves as the container for `VolumeInfo` partitions.

## Architecture Overview
-   **Pattern**: Data Object / Parcelable.
-   **Source**: Populated by `vold` (Volume Daemon) and passed to `StorageManagerService`.
-   **Relationship**: One Disk -> Many Volumes (`volumeCount`).

## Data Model
-   **Identity**: `id` (String), `sysPath` (String).
-   **Attributes**: `size` (long), `label` (String).
-   **Flags** (`flags` int bitmask):
    -   `FLAG_ADOPTABLE`: Can be formatted as internal storage.
    -   `FLAG_DEFAULT_PRIMARY`: Is the default primary storage (rare for removables).
    -   `FLAG_SD`, `FLAG_USB`: Hardware type.
    -   `FLAG_STUB_VISIBLE`: Visibility flag for ChromeOS/ARC++.

## API Reference
-   `getDescription()`: Returns localized description (e.g., "SanDisk SD Card").
-   `isAdoptable()`, `isSd()`, `isUsb()`: capability checks.

## Java-to-C++ Translation Guide
-   **Source of Truth**: This class mirrors `android::vold::Disk` in `system/vold`. The Parceling logic must match the C++ Binder serialization exactly.
-   **Parcel Order**: ID, Flags, Size, Label, VolumeCount, SysPath.
