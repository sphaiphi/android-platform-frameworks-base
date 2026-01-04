# Editable - Reverse Engineering Documentation

## Executive Summary
Interface for mutable text. Extends `CharSequence`, `GetChars`, `Spannable`, `Appendable`.

## API Reference
- **`replace(int st, int en, CharSequence source, int start, int end)`**: Replaces range.
- **`insert(...)`**: Convenience for replace.
- **`delete(...)`**: Convenience for replace.
- **`append(...)`**: Appends text.
- **`clear()`**: Clears text.
- **`clearSpans()`**: Removes all spans.
- **`setFilters(InputFilter[])`**: Sets filters to modify/reject changes.

## Java-to-C++ Translation Guide
- **Concept**: Mutable string with markup.
- **Core**: `SpannableStringBuilder` is the main implementation.
