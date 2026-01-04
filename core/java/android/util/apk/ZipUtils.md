# ZipUtils - Reverse Engineering Documentation

## Executive Summary
Helper class to parse ZIP file structures, specifically finding the End of Central Directory (EoCD) record. This is crucial for finding the APK Signing Block, which lives between the Central Directory and the EoCD.

## Key Algorithms
*   **`findZipEndOfCentralDirectoryRecord`**:
    *   Scans backwards from the end of the file.
    *   Looks for signature `0x06054b50`.
    *   Validates comment length field matches the actual file size.
*   **`isZip64`**: Checks for Zip64 locator. (Note: Android often rejects Zip64 for APKs).

## Java-to-C++ Translation Guide
*   **Binary Parsing**: Direct byte manipulation. Easy to port.