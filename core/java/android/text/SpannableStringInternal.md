# SpannableStringInternal - Reverse Engineering Documentation

## Executive Summary
Base class for `SpannableString` and `SpannedString`. Manages fixed text and a fixed set of spans (though `SpannableString` allows changing the span objects, the text remains fixed).

## Data Model
- **`mText`**: String.
- **`mSpans`**: Object array.
- **`mSpanData`**: Int array (Start, End, Flags) packed.
- **`mSpanCount`**: Number of spans.

## Java-to-C++ Translation Guide
- **Optimization**: Uses parallel arrays for span data to avoid object overhead.
