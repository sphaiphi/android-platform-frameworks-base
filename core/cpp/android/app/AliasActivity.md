# AliasActivity - Reverse Engineering Documentation

## Executive Summary
`AliasActivity` is a deprecated stub activity used to launch another activity based on meta-data in the manifest. It essentially acts as a redirector.

## Architecture Overview
*   **Inheritance**: Extends `Activity`.
*   **Mechanism**: parses `AndroidManifest.xml` meta-data (`android.app.alias`) to find a target Intent and launches it.

## Detailed Functionality

### Initialization (`onCreate`)
1.  **Load Meta-Data**: Calls `getPackageManager().getActivityInfo()` with `GET_META_DATA`.
2.  **Parse XML**: Loads the XmlResourceParser referenced by `ALIAS_META_DATA` ("android.app.alias").
3.  **Parse Intent**: Looks for an `<intent>` tag inside the `<alias>` tag in the XML.
4.  **Launch**: Calls `startActivity(intent)` with the parsed intent.
5.  **Finish**: Calls `finish()` to remove itself from the back stack.

## Java-to-C++ Translation Guide
*   **Low Priority**: This is deprecated and rarely used in modern apps.
*   **XML Parsing**: Would require an XML parser to read the resource.
*   **Intent Resolution**: Requires `PackageManager` access.

## Implementation Risks
*   **Obsolete**: Functionality is better handled by `<activity-alias>` tag in the manifest directly handled by the OS/Launcher, rather than this Java-level redirector. Implementation might be unnecessary.
