# JsonWriter - Reverse Engineering Documentation

## Executive Summary
A streaming JSON writer. Writes tokens to an underlying `Writer`.

## Architecture Overview
*   **State Machine**: Uses a `stack` of `JsonScope` to ensure correct JSON structure (e.g., matching braces, comma insertion).
*   **Formatting**: Supports indentation for pretty-printing.

## Key Algorithms
*   **`beginObject`/`endObject`**: Pushes/pops scope, writes `{` / `}`.
*   **`name`**: Writes property name, inserts `,` or `:` as needed based on context.
*   **`value`**: Writes value (string, number, boolean, null). Escapes strings.

## Java-to-C++ Translation Guide
*   **Stream**: Maps to `std::ostream` or a buffer.
*   **State**: `std::vector<JsonScope>` stack.

## Implementation Risks
*   **Validation**: Prevents invalid JSON (e.g., multiple top-level values, missing names in objects).
