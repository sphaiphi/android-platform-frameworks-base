# WallpaperManager - Reverse Engineering Documentation

## Executive Summary
`WallpaperManager` is the primary system service for managing the device's wallpaper (both static images and live services). it provides APIs to set the wallpaper from bitmaps, resources, or streams, query current wallpaper metadata and colors, and manage display-specific offsets and zooms. It also handles the complex logic of multi-crop support for different display dimensions and coordinates with the `WallpaperManagerService` in the system server.

## Architecture Overview
- **Service Integration**: Managed by `SystemServiceRegistry` and accessible via `Context.WALLPAPER_SERVICE`.
- **Backend Communication**: Acts as a client wrapper for the `IWallpaperManager` AIDL interface.
- **Core Components**:
    - `Globals`: A singleton that manages internal caches for the current wallpaper bitmap and handles color change callbacks from the system server.
    - `ColorManagementProxy`: Handles wide color gamut (WCG) management for decoded wallpapers.
    - `WallpaperSetCompletion`: Internal synchronization primitive to wait for the system server to finish processing a set-wallpaper request.
- **State**: Tracks wallpaper offsets, steps, and zoom levels per window.

## Detailed Functionality

### Setting Wallpapers (`setBitmap`, `setStream`, `setResource`)
**Purpose**: Updating the system or lock screen imagery.
**Logic**:
1. Checks for `SET_WALLPAPER` permission.
2. If multi-crop is enabled, it prepares multiple crop hints for different orientations.
3. Opens a `ParcelFileDescriptor` to the system server.
4. Compresses and writes the image data to the PFD.
5. Waits for the `WallpaperSetCompletion` signal to ensure the operation is finalized.

### Wallpaper Retrieval
**Purpose**: Fetching current imagery or metadata.
**Mechanism**:
- `getDrawable()`: Retrieves the current bitmap, utilizing `sGlobals` cache if possible. Requires significant permissions (`MANAGE_EXTERNAL_STORAGE` on newer versions).
- `getWallpaperInfo()`: Returns `WallpaperInfo` if a live wallpaper is active.
- `getWallpaperColors()`: Returns the extracted `WallpaperColors` profile.

### Multi-Crop Logic
**Purpose**: Ensuring the wallpaper looks good on devices with varying screen sizes (e.g., foldables).
**Logic**: Supports mapping specific `Rect` crops to different screen orientations (`ORIENTATION_PORTRAIT`, `LANDSCAPE`, etc.). Uses `getBitmapCrops` to simulate how an image will be adjusted.

### Layout Control
**Purpose**: Parallax and interactive effects.
**Logic**:
- `setWallpaperOffsets`: Moves the wallpaper behind a window based on 0.0-1.0 coordinates.
- `setWallpaperZoomOut`: Applies a scale factor to the wallpaper layer.

## API Reference (Key Methods)
- `public void setBitmap(Bitmap bitmap)`: Main update API.
- `public WallpaperColors getWallpaperColors(int which)`: Visual profile lookup.
- `public void suggestDesiredDimensions(int width, int height)`: Layout hint for launchers.
- `public void addOnColorsChangedListener(...)`: Event registration.

## Java-to-C++ Translation Guide
- **AIDL Integration**: Use AIDL-generated C++ interface `android::app::IWallpaperManager`.
- **Bitmap Handling**: Use `android::graphics::Bitmap` and native image decoders (like `libjpeg-turbo` or `libpng`) for stream manipulation.
- **File Transfer**: Use `android::base::unique_fd` to manage `ParcelFileDescriptor` objects.
- **Caching**: Replicate the `CachedWallpaper` logic using native LRU or simple singleton patterns.

## Implementation Risks
- **Permission Complexity**: Wallpaper access is a major privacy concern. C++ implementation must strictly enforce the `READ_WALLPAPER_INTERNAL` and `MANAGE_EXTERNAL_STORAGE` permission checks.
- **Memory Consumption**: High-resolution wallpapers consume significant RAM. C++ logic must be aggressive about recycling bitmaps and using shared memory (ashmem) where appropriate.
- **Race Conditions**: Multiple apps setting wallpapers simultaneously or rapid offset updates must be handled via Binder synchronization.
