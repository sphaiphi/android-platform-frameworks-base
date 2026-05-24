# FontManager - Reverse Engineering Documentation

## Executive Summary
`FontManager` is the system service (`Context.FONT_SERVICE`) responsible for managing system fonts. It allows updating font families and retrieving the current font configuration.

## Architecture Overview
-   **System Service**: Wraps `IFontManager` (Binder interface).
-   **Permissions**: Operations require `Manifest.permission.UPDATE_FONTS`.
-   **Error Codes**: Defines integer constants for various success/failure scenarios (e.g., `RESULT_SUCCESS`, `RESULT_ERROR_VERIFICATION_FAILURE`).

## Detailed Functionality
-   **`getFontConfig()`**: Retrieves the current system `FontConfig`.
-   **`updateFontFamily()`**: The core API for updates.
    1.  Accepts a `FontFamilyUpdateRequest` and a `baseVersion`.
    2.  Translates the high-level request into a list of internal `FontUpdateRequest` objects (AIDL parcelables).
    3.  Calls `mIFontManager.updateFontFamily`.

## Data Model (Result Codes)
-   `RESULT_SUCCESS` (0)
-   `RESULT_ERROR_FAILED_TO_WRITE_FONT_FILE` (-1)
-   `RESULT_ERROR_VERIFICATION_FAILURE` (-2)
-   `RESULT_ERROR_INVALID_FONT_FILE` (-3)
-   `RESULT_ERROR_INVALID_FONT_NAME` (-4)
-   `RESULT_ERROR_DOWNGRADING` (-5)
-   `RESULT_ERROR_FAILED_UPDATE_CONFIG` (-6)
-   `RESULT_ERROR_FONT_UPDATER_DISABLED` (-7)
-   `RESULT_ERROR_VERSION_MISMATCH` (-8)
-   `RESULT_ERROR_FONT_NOT_FOUND` (-9)
-   (Shell-only error codes < -10000)

## Java-to-C++ Translation Guide
-   **Service Proxy**: This is the client-side proxy. The C++ equivalent would likely be a client library interacting with the `fonts` system service.
-   **Binder**: Uses `IFontManager` which maps to `BpFontManager` in C++.

## Source Reference
Defined in `FontManager.java`.
