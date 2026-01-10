# PrintServiceInfo - Reverse Engineering Documentation

## Executive Summary
`PrintServiceInfo` describes an installed print service, including its component name, settings activities, and configuration options parsed from its manifest metadata.

## Architecture Overview
- **Type**: Parcelable Data Class.
- **Factory**: `create(Context, ResolveInfo)` parses XML metadata.

## Detailed Functionality
-   **Metadata Parsing**: Reads `android.printservice` metadata tag.
-   **Attributes**:
    -   `settingsActivity`: Custom settings UI.
    -   `addPrintersActivity`: UI to manually add printers.
    -   `advancedPrintOptionsActivity`: UI for job-specific advanced options.

## Java-to-C++ Translation Guide
-   **XML Parsing**: The parsing logic (`loadXmlMetaData`) is specific to Android Resources. C++ would need access to the APK assets or rely on the Java layer to pass this info.
