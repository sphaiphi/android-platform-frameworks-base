# PreferenceInflater - Reverse Engineering Documentation

## Executive Summary
`PreferenceInflater` specializes `GenericInflater` to inflate `Preference` hierarchies from XML.

**Note:** This class is deprecated and hidden.

## Architecture Overview
- **Inheritance**: `PreferenceInflater` -> `GenericInflater`.

## Detailed Functionality
-   **Package Default**: Defaults to searching the `android.preference.` package.
-   **Intent Parsing**: Handles `<intent>` tags inside preferences.
-   **Extra Parsing**: Handles `<extra>` tags.

## Java-to-C++ Translation Guide
-   **XML Parsing**: See `GenericInflater`.
-   **Intents**: Logic to parse intent actions/extras from XML.
