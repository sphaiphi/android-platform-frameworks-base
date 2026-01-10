# KeymasterDefs - Reverse Engineering Documentation

## Executive Summary
`KeymasterDefs` contains constants defining Keymaster tag types, tags, algorithms, padding modes, error codes, etc.

## Architecture Overview
*   **Package**: `android.security.keymaster`
*   **Type**: Final Class (Constants)
*   **Sync Requirement**: Must match `hardware/libhardware/include/hardware/keymaster_defs.h`.

## Detailed Functionality
*   **Tag Types**: Mask bits to define type (Enum, Uint, etc.).
*   **Tags**: `KM_TAG_PURPOSE`, `KM_TAG_ALGORITHM`, etc.
*   **Values**: Algorithms (`KM_ALGORITHM_RSA`), Block Modes, etc.
*   **Error Codes**: `KM_ERROR_OK`, `KM_ERROR_UNSUPPORTED_PURPOSE`, etc.
*   **Helpers**: `getTagType(int tag)`, `getErrorMessage(int errorCode)`.

## Java-to-C++ Translation Guide
*   These are direct mappings of C++ `enum` values from the Keymaster HAL. The C++ implementation should use the official HAL headers directly.
