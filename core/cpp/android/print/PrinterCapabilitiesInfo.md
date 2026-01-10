# PrinterCapabilitiesInfo - Reverse Engineering Documentation

## Executive Summary
`PrinterCapabilitiesInfo` describes the capabilities of a specific printer. It is created by print services to inform the system what a printer supports (media sizes, resolutions, etc.).

## Architecture Overview
- **Type**: Parcelable Data Class (final).
- **Builder**: `Builder` class ensures validity (must have defaults).

## Detailed Functionality
-   **Lists of Supported Attributes**: MediaSizes, Resolutions.
-   **Bitmasks**: ColorModes, DuplexModes.
-   **Defaults**: Stores the index/value of the default option for each attribute.
-   **Validation**: Builder enforces that at least one option is added and defaults are set.

## Data Model
-   `mMediaSizes`: List<MediaSize>
-   `mResolutions`: List<Resolution>
-   `mMinMargins`: Margins
-   `mColorModes`: int (mask)
-   `mDuplexModes`: int (mask)
-   `mDefaults`: int[] (indices/values)

## Java-to-C++ Translation Guide
-   **Defaults Logic**: The logic storing defaults as indices into the lists (`mDefaults[PROPERTY_MEDIA_SIZE]`) is specific and compact; preserve it or use a more C++ idiomatic approach (e.g., pointers/iterators) if serialization format allows (it doesn't, so stick to indices for IPC).
