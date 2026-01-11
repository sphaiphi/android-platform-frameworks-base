# TextUtils - Reverse Engineering Documentation

## Executive Summary
Collection of string utilities.

## Core Functions
- **`ellipsize`**: Calculates text truncation and ellipsis placement. Uses `MeasuredParagraph`.
- **`expandTemplate`**: Replaces `^1`, `^2` placeholders.
- **`split`, `join`**: String manipulation.
- **`htmlEncode`**: Escapes XML/HTML chars.
- **`getReverse`**: Reverses string (deprecated).
- **`isGraphic`**: Checks for printable characters.
- **`copySpansFrom`**: Utilities for span copying.

## Java-to-C++ Translation Guide
- **Ellipsize**: Needs careful porting of the binary search logic using measured widths.
- **General**: Standard string util library functions.
