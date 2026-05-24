# Spanned - Reverse Engineering Documentation

## Executive Summary
Interface for text with markup. Defines constants for span flags (Exclusive/Inclusive, Priority, etc.).

## Constants
- **`SPAN_INCLUSIVE_EXCLUSIVE`**, `SPAN_EXCLUSIVE_INCLUSIVE`, etc.: Define behavior at edges when inserting text.
- **`SPAN_PARAGRAPH`**: Span affects the whole paragraph.
- **`SPAN_PRIORITY`**: Z-ordering.

## API Reference
- **`getSpans(int start, int end, Class type)`**: Query spans.
- **`getSpanStart(Object tag)`**: Get start offset.
- **`getSpanEnd(Object tag)`**: Get end offset.
- **`getSpanFlags(Object tag)`**: Get flags.
- **`nextSpanTransition(...)`**: Iterate span boundaries.

## Java-to-C++ Translation Guide
- **Interface**: Defines read access to markup.
