# WallpaperInfo - Reverse Engineering Documentation

## Executive Summary
`WallpaperInfo` specifies meta-information about a wallpaper service (Live Wallpaper). It parses the XML metadata associated with a `WallpaperService` declaration in the manifest, extracting details like the settings activity, thumbnail, author, description, and support for advanced features like multiple displays or ambient mode.

## Architecture Overview
- **Structure**:
    - `mService`: `ResolveInfo` about the background service.
    - `mSettingsActivityName`: Name of the configuration activity.
    - `mThumbnailResource`: ID for the preview image.
    - `mAuthorResource`, `mDescriptionResource`: Localized text resources.
    - **Flags**: `mSupportsAmbientMode`, `mSupportMultipleDisplays`, `mShowMetadataInPreview`.
- **Inheritance**: Implements `Parcelable`.

## Detailed Functionality

### Metadata Parsing
**Purpose**: Reading the `android.service.wallpaper` XML file.
**Algorithm**:
1. Loads the XML parser for the service's metadata.
2. Identifies the `<wallpaper>` root tag.
3. Maps XML attributes (e.g., `android:settingsActivity`, `android:author`) to internal fields.
4. Detects support for ambient mode, defaulting to `true` on watch devices.

### Localized Resource Loading
**Mechanism**:
- `loadLabel`, `loadIcon`: Proxies to the `ResolveInfo` to get service-level branding.
- `loadAuthor`, `loadDescription`: Uses the `PackageManager` to retrieve strings from the service's package using the stored resource IDs.

## API Reference
- `public ComponentName getComponent()`: Returns the service identity.
- `public String getSettingsActivity()`: Returns the config UI name.
- `public boolean supportsMultipleDisplays()`: Multi-monitor support check.
- `public Uri getSettingsSliceUri()`: Returns the settings UI slice.

## Java-to-C++ Translation Guide
- **XML Parsing**: Use a native XML parser to read the service metadata.
- **Resource Management**: Use `android::res::AssetManager` to resolve string and drawable IDs.
- **Component Handling**: Use `android::content::ComponentName` and `android::content::pm::ResolveInfo` equivalents.

## Implementation Risks
- **Manifest Synchronization**: The attribute names in the XML must perfectly match the `com.android.internal.R.styleable.Wallpaper` definitions.
- **Permission Scope**: Accessing metadata for other apps requires `QUERY_ALL_PACKAGES` visibility on modern Android.
- **Robustness**: Parsing must handle missing attributes or invalid resource IDs without crashing the system server.
