# WallpaperBackupHelper - Reverse Engineering Documentation

## Executive Summary
Legacy helper for restoring old wallpaper backups. No longer performs backups (no-op).

## Detailed Functionality
-   **Backup**: No-op.
-   **Restore**:
    -   Checks for specific legacy keys.
    -   Writes data to a temporary stage file.
    -   Calls `WallpaperManager.setStream` to apply.

## Java-to-C++ Translation Guide
-   Likely not needed unless the C++ agent needs to support migration from very old Android versions (pre-N). If so, needs `WallpaperManager` interaction.
