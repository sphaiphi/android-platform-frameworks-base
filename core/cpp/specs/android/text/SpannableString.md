# SpannableString - Reverse Engineering Documentation

## Executive Summary
Immutable text content with mutable spans. Extends `SpannableStringInternal`.

## API Reference
- **`setSpan`**: Calls super.
- **`removeSpan`**: Calls super.
- **`subSequence`**: Returns new `SpannableString`.

## Java-to-C++ Translation Guide
- **Implementation**: Wrapper around `SpannableStringInternal`.
