# WallpaperDescription - Reverse Engineering Documentation

## Executive Summary
`WallpaperDescription` is a data class used to describe a specific instance of a wallpaper (either static or live). It acts as a communication object between the wallpaper rendering service, the wallpaper chooser UI, and the `WallpaperManager`. Unlike `WallpaperInfo`, which describes a wallpaper *component* (a class), `WallpaperDescription` describes a specific configuration or instance of that component, including distinct metadata like cropping, specific content URIs, and descriptions.

## Architecture Overview
- **Package**: `android.app.wallpaper`
- **Implements**: `Parcelable`
- **Role**: Data Transfer Object (DTO) for wallpaper metadata.
- **Relationships**:
  - Used by `WallpaperInstance`.
  - Used by `WallpaperManager`.
  - Contains `ComponentName`, `Uri`, `PersistableBundle`.

## Detailed Functionality

### Core Data storage
**Purpose**: Holds all necessary metadata to reconstruct a wallpaper state.
**Fields**:
- `component`: The `ComponentName` of the service (null for static images).
- `id`: Unique identifier for this instance.
- `thumbnail`: URI for the thumbnail image.
- `title`, `description`: UI-facing text.
- `contextUri`, `contextDescription`: Action link associated with the wallpaper.
- `content`: A `PersistableBundle` for arbitrary extra data (e.g., asset IDs).
- `cropHints`: A mapping of screen orientations (Portrait, Landscape, etc.) to crop rectangles (`Rect`).
- `sampleSize`: Float value indicating downsampling ratio.

### XML Serialization (`saveToXml`, `restoreFromXml`)
**Purpose**: Persist the description to storage (likely disk) and restore it.
**Algorithm**:
1.  **Save**:
    - Serializes basic attributes (component, id, thumbnail, etc.) as XML attributes.
    - Serializes `cropHints` by iterating through known screen orientations (Portrait, Landscape, Square types) and writing "cropLeft/Top/Right/Bottom" + OrientationName attributes.
    - Writes `description` lines as child tags `<description descriptionline="..." />`.
    - Writes `content` (`PersistableBundle`) inside a `<content>` tag.
2.  **Restore**:
    - Parses attributes from the XML start tag.
    - Reconstructs `cropHints` by looking for specific attribute naming patterns.
    - Iterates child tags to populate `description` list and `content` bundle.

### Parcelable Implementation
**Purpose**: Efficient IPC transport.
**Algorithm**:
- Writes fields sequentially to the `Parcel`.
- `cropHints` are flattened by iterating predefined orientation keys and writing `Rect` objects if present.

### Builder Pattern
**Purpose**: Construct immutable `WallpaperDescription` instances.
**Notes**: Standard builder pattern with setters for all fields.

## Data Model

| Field | Type | Description |
|-------|------|-------------|
| `mComponent` | `ComponentName` | Service component (nullable). |
| `mId` | `String` | Unique instance ID. |
| `mThumbnail` | `Uri` | Thumbnail image URI. |
| `mTitle` | `CharSequence` | Display title. |
| `mDescription` | `List<CharSequence>` | Lines of description text. |
| `mContextUri` | `Uri` | Action URI. |
| `mContextDescription` | `CharSequence` | Action link text. |
| `mContent` | `PersistableBundle` | Arbitrary key-value data. |
| `mCropHints` | `SparseArray<Rect>` | Map of `ScreenOrientation` int -> `Rect`. |
| `mSampleSize` | `float` | Image downsampling factor. |

## API Reference

### `saveToXml(TypedXmlSerializer out)`
- **Preconditions**: `out` is a valid serializer at the correct tag depth.
- **Side effects**: Writes XML attributes and child tags.
- **Exceptions**: `IOException`, `XmlPullParserException`.

### `restoreFromXml(TypedXmlPullParser in)`
- **Returns**: New `WallpaperDescription` instance.
- **Preconditions**: `in` is positioned at the start tag of the description.

## Java-to-C++ Translation Guide

- **Strings**: Use `std::string` or `android::String16` depending on unicode requirements. The Java code uses `CharSequence` and handles HTML via `Html.toHtml`/`fromHtml`. C++ implementation may need a simplified text handler or strip HTML if the UI layer handles rendering elsewhere.
- **Parcelable**: Implement `android::Parcelable` interface.
  - `ComponentName` -> `android::content::ComponentName` (C++ equivalent needed).
  - `Uri` -> `android::net::Uri` (or string representation if just for storage).
  - `Rect` -> `android::graphics::Rect`.
  - `PersistableBundle` -> `android::os::PersistableBundle`.
  - `SparseArray<Rect>` -> `std::map<int, Rect>` or `std::vector<std::pair<int, Rect>>`.
- **XML Parsing**: The Java code uses `TypedXmlSerializer`/`TypedXmlPullParser`. C++ should use `libxml2` or Android's internal XML parsing utilities available in the native framework.
- **Comparisons**: `equals` and `hashCode` rely on `component` and `id`.

## Implementation Risks
- **HTML Handling**: Java's `Html.fromHtml` behaves specifically regarding trailing whitespace (see `removeTrailingWhitespace`). C++ logic must replicate this if bit-exact string parity is required, though mostly likely the raw string or stripped string is sufficient.
- **Parcel Compatibility**: Ensure the write order in C++ matches Java exactly for IPC.
- **SparseArray serialization**: The manual iteration over specific screen orientations (`screenDimensionPairs`) in XML serialization is a business logic detail that must be copied exactly.

## Questions for C++ Team
- Do we have a native equivalent for `PersistableBundle`?
- Is HTML text formatting supported or required in the native layer, or is it opaque text?
