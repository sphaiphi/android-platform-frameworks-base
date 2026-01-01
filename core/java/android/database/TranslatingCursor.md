# TranslatingCursor - Reverse Engineering Documentation

## Executive Summary
`TranslatingCursor` wraps a cursor and transforms data in specific columns on-the-fly. It is often used to migrate legacy file paths (`_data` column) to Content URIs transparently.

## Architecture Overview
*   **Inheritance**: `CrossProcessCursorWrapper`.
*   **Components**: `Config` (columns to translate), `Translator` (functional interface).

## Detailed Functionality
*   **Query**: Static `query` helper splicing auxiliary columns if needed.
*   **Access**:
    *   `getString(columnIndex)`: If column needs translation, call `mTranslator.translate(...)`.
    *   Other types (`getInt`, `getDouble`): Throw `IllegalArgumentException` if accessed on a translated column (translation assumes String output).
*   **Window**: Like `RedactingCursor`, overrides `fillWindow` to ensure translation logic runs. Returns `null` for `getWindow` to prevent data leak.

## Java-to-C++ Translation Guide
*   **Function Pointer**: `Translator` is a lambda/function pointer.
*   **String Manipulation**: Heavy string processing implies potential performance cost.
