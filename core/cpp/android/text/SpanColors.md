# SpanColors - Reverse Engineering Documentation

## Executive Summary
Helper class to determine the foreground color at a specific index in `Spanned` text by coalescing multiple spans.

## Algorithm
- Uses `SpanSet<CharacterStyle>` to find spans covering the index.
- Iterates spans, calls `updateDrawState(TextPaint)`.
- Returns the final color from the paint.

## Java-to-C++ Translation Guide
- **Painting**: Emulates the painting process to determine attributes without drawing.
