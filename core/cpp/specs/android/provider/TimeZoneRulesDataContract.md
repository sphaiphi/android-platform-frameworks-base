# TimeZoneRulesDataContract - Reverse Engineering Documentation

## Executive Summary
`TimeZoneRulesDataContract` defines the contract for the Time Zone updater application to expose time zone rules updates.

## Architecture Overview
- **Authority**: `com.android.timezone`.
- **Inner Class**: `Operation`.

## Detailed Functionality
-   **Operation Type**: `INSTALL`, `UNINSTALL`, `NOOP`.
-   **Versioning**: `distro_major_version`, `distro_minor_version`, `rules_version`, `revision`.
-   **Data Access**: `openFile` on the operation URI returns the distro parcel file descriptor.

## API Reference
-   `Operation.CONTENT_URI`: `content://com.android.timezone/operation`.

## Java-to-C++ Translation Guide
-   **URI**: `content://com.android.timezone/operation`.
-   **Enum**: Map `TYPE_INSTALL`, etc. to C++ enums.
