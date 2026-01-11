# PrintAttributes - Reverse Engineering Documentation

## Executive Summary
`PrintAttributes` encapsulates the configuration for a print job, including media size, resolution, margins, color mode, and duplex mode. It serves as the primary way to communicate print constraints and user selections between the system, the print service, and the application.

## Architecture Overview
- **Type**: Parcelable Data Class (final).
- **Builder Pattern**: Uses an inner `Builder` class for construction.
- **Components**: Contains nested static classes `MediaSize`, `Resolution`, and `Margins`.

## Detailed Functionality
-   **MediaSize**: Defines physical paper dimensions (e.g., ISO_A4, NA_LETTER). Supports localized labels and unique IDs. Handles portrait/landscape swapping.
-   **Resolution**: Defines DPI (horizontal/vertical).
-   **Margins**: Defines physical margins in mils (thousandths of an inch).
-   **Color Mode**: Monochrome or Color.
-   **Duplex Mode**: None, Long Edge, or Short Edge.
-   **Orientation**: Inferred from `MediaSize` (width vs height).

## Data Model
-   `mMediaSize`: `MediaSize`
-   `mResolution`: `Resolution`
-   `mMinMargins`: `Margins`
-   `mColorMode`: int (bitmask/value)
-   `mDuplexMode`: int (bitmask/value)

## API Reference
-   **Getters/Setters**: `getMediaSize`, `setMediaSize`, etc.
-   **Orientation**: `isPortrait()`, `asPortrait()`, `asLandscape()`.
-   **Parcelable**: `writeToParcel`, `createFromParcel`.

## Java-to-C++ Translation Guide
-   **Nested Classes**: C++ nested classes or separate structs.
-   **Predefined Constants**: `MediaSize` has a huge list of constants (ISO_A4, etc.) which should be replicated as static consts or a lookup table.
-   **Validation**: Ensure setters enforce valid bitmasks/ranges.
