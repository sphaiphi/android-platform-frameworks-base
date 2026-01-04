# AlteredCharSequence - Reverse Engineering Documentation

## Executive Summary
`AlteredCharSequence` is a `CharSequence` implementation that wraps a source `CharSequence` and replaces a specific range of characters with a different character array. It is primarily used to "mirror" text with a modification without copying the entire content.

## Data Model
- **`mSource`** (`CharSequence`): The underlying source text.
- **`mChars`** (`char[]`): The character array containing the replacement text.
- **`mStart`** (`int`): The start offset in the source text where the replacement begins.
- **`mEnd`** (`int`): The end offset in the source text where the replacement ends.

## API Reference
- **`make(CharSequence source, char[] sub, int substart, int subend)`**: Static factory method. Returns an `AlteredSpanned` if source is `Spanned`, otherwise `AlteredCharSequence`.
- **`charAt(int off)`**: Returns char from `mChars` if `off` is within `[mStart, mEnd)`, otherwise from `mSource`.
- **`length()`**: Returns `mSource.length()`.
- **`subSequence(int start, int end)`**: Returns a new `AlteredCharSequence` representing the subsequence.
- **`getChars(int start, int end, char[] dest, int off)`**: Copies chars. Uses `TextUtils.getChars` for source, then overlays `mChars` for the altered range.
- **`toString()`**: Converts the entire sequence to a String.

### Inner Class: `AlteredSpanned`
Extends `AlteredCharSequence` and implements `Spanned`. Delegates all `Spanned` methods (`getSpans`, `getSpanStart`, etc.) to the source text (casted to `Spanned`).

## Java-to-C++ Translation Guide
- **Concept**: A view over a string with a "patch".
- **Types**:
    - `CharSequence` -> `std::u16string_view` or a custom abstract string class.
    - `char[]` -> `const char16_t*` or `std::vector<char16_t>`.
- **Memory**: The C++ implementation should manage the lifetime of the `sub` array if it's not owned elsewhere, or copy it.
- **Inheritance**: `AlteredSpanned` needs to implement the C++ equivalent of the `Spanned` interface.
