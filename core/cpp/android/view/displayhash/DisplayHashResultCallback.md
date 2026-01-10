# DisplayHashResultCallback - Reverse Engineering Documentation

## Executive Summary
Interface for receiving the result of an asynchronous display hash generation request (triggered via `View#generateDisplayHash`).

## Error Codes
*   `SUCCESS`: Result delivered via `onDisplayHashResult`.
*   `ERROR_UNKNOWN` (-1)
*   `ERROR_INVALID_BOUNDS` (-2)
*   `ERROR_MISSING_WINDOW` (-3)
*   `ERROR_NOT_VISIBLE_ON_SCREEN` (-4)
*   `ERROR_INVALID_HASH_ALGORITHM` (-5)
*   `ERROR_TOO_MANY_REQUESTS` (-6) (Throttling)

## Java-to-C++ Translation Guide
*   **Interface**: Abstract callback class.
