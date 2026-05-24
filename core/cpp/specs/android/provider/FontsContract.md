# FontsContract - Reverse Engineering Documentation

## Executive Summary
`FontsContract` utility class for dealing with Font ContentProviders. It handles the details of requesting fonts, including threading (via `HandlerThread`) and caching (`LruCache`).

**Note**: Deprecated in favor of `androidx.core.provider.FontsContractCompat`.

## Architecture Overview
- **Role**: Client utility for Font Providers.
- **Mechanism**:
    1.  `fetchFonts`: Queries the provider to get file IDs / file descriptors.
    2.  `buildTypeface`: Reads the file descriptors (often using mmap) to create a `Typeface`.

## Detailed Functionality
-   **Columns**: `FILE_ID`, `TTC_INDEX`, `VARIATION_SETTINGS`, `WEIGHT`, `ITALIC`, `RESULT_CODE`.
-   **Sync/Async**: `getFontSync`, `requestFonts`.
-   **Retry Logic**: Handles timeouts and thread management.

## Java-to-C++ Translation Guide
-   **Typeface**: C++ has `SkTypeface` / `minikin`. This class bridges the gap between a ContentProvider `ParcelFileDescriptor` and the graphics subsystem.
-   **MMap**: Uses `FileChannel.map` or native `mmap` to read font data.
