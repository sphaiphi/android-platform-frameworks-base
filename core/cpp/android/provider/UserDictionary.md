# UserDictionary - Reverse Engineering Documentation

## Executive Summary
`UserDictionary` defines the contract for the user-defined word list, used by IMEs for predictive text.

## Architecture Overview
- **Authority**: `user_dictionary`.
- **Inner Class**: `Words`.

## Detailed Functionality
-   **Data**: Stores words, frequency (1-255), locale, and an optional shortcut.
-   **Operations**: Insert (addWord), Query.

## Data Model
-   **Columns**: `word`, `frequency`, `locale`, `appid`, `shortcut`.

## Java-to-C++ Translation Guide
-   **URI**: `content://user_dictionary/words`.
-   **Usage**: Input methods in C++ (if any) would query this to augment dictionaries.
