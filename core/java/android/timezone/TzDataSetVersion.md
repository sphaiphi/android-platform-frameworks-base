# TzDataSetVersion - Reverse Engineering Documentation

## Executive Summary
`TzDataSetVersion` represents versioning information for the time zone data installed on the device. It includes major/minor format versions, the IANA rules version, and an Android revision number. Wraps `com.android.i18n.timezone.TzDataSetVersion`.

## Architecture Overview
Provides static methods to read the version from disk and accessors to inspect the version components.

## Data Model
*   **`mDelegate`**: `com.android.i18n.timezone.TzDataSetVersion`.

### Inner Class
*   **`TzDataSetException`**: Checked exception for errors encountered while reading version data.

## API Reference
*   **`currentFormatMajorVersion()`**: Static. Returns expected major version.
*   **`currentFormatMinorVersion()`**: Static. Returns expected minor version.
*   **`isCompatibleWithThisDevice(TzDataSetVersion)`**: Static. Checks compatibility.
*   **`read()`**: Static. Reads the currently active time zone module version file.
*   **`getFormatMajorVersion()`**: Instance.
*   **`getFormatMinorVersion()`**: Instance.
*   **`getRulesVersion()`**: Instance. (e.g., "2020a").
*   **`getRevision()`**: Instance. Android specific revision.

## Java-to-C++ Translation Guide
*   **File I/O**: The `read()` method involves reading a specific version file (typically `/apex/com.android.tzdata/etc/tz/tz_version`). C++ logic should replicate parsing this file format.
*   **Compatibility Logic**: Logic for major/minor version compatibility checks.

## Implementation Risks
*   **File Paths**: Hardcoded paths to timezone data module files are likely involved in the delegate.
