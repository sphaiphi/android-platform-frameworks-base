# JsonReader - Reverse Engineering Documentation

## Executive Summary
A streaming JSON parser (pull parser) complying roughly with RFC 4627. Reads tokens (null, boolean, number, string, object start/end, array start/end) sequentially.

## Architecture Overview
*   **State Machine**: Maintains a `stack` of `JsonScope` (EMPTY_ARRAY, NONEMPTY_OBJECT, etc.) to validate nesting and syntax.
*   **Buffer**: Uses a char buffer (`1024` chars) to read chunks from the `Reader`.
*   **String Pool**: Uses `StringPool` to deduplicate strings (keys/values) to save memory.

## Key Algorithms
*   **`peek()`**: Looks at the next token type without consuming.
*   **`nextValue()` / `advance()`**: Consumes token.
*   **Literals**: Reads `true`, `false`, `null` by checking chars.
*   **Numbers**: Reads numbers as strings but verifies format.
*   **Strings**: Handles escaping (`"`, `\`, `‪`XXXX).
*   **Lenient Mode**: Allows comments, unquoted names, single quotes if `setLenient(true)`.

## Java-to-C++ Translation Guide
*   **Pull Parser**: Similar to `RapidJSON` or `JsonCpp` SAX style, but this is a pull API. C++ implementation would maintain a cursor into the buffer.
*   **String Pooling**: Can be implemented with `std::unordered_set<std::string>` or `std::string_view` if the input buffer lifetime allows.

## Implementation Risks
*   **Recursion**: Uses a stack for scope, avoiding deep C++ recursion stack overflow, but the stack size should be limited.
*   **BOM**: Handles Byte Order Mark.
