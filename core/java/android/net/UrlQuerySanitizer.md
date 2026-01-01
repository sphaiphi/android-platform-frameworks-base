# UrlQuerySanitizer.java - Reverse Engineering Documentation

## Executive Summary
`UrlQuerySanitizer` cleans up URL query parameters. It allows defining rules (sanitizers) for specific parameters to filter out illegal characters (e.g., script injection attacks, special characters).

## Architecture Overview
- **Type**: Utility / Parser
- **Package**: `android.net`.

## Detailed Functionality
-   **Parsing**: Splits query by `&` and `=`. Decodes values.
-   **Sanitization**:
    -   `ValueSanitizer` interface.
    -   `IllegalCharacterValueSanitizer`: Filters characters based on flags (SPACE_OK, SCRIPT_URL_OK, etc.).
-   **Registration**: Allows registering specific sanitizers for specific parameter names.
-   **Defaults**: `mUnregisteredParameterValueSanitizer` handles unknown params (default: `getAllIllegal` - very strict).

## Java-to-C++ Translation Guide
-   String parsing and manipulation.
-   `IllegalCharacterValueSanitizer` is a state machine checking char codes.
-   Useful for input validation in C++ networking components.
