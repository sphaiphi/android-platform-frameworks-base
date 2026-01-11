# GraphemeClusterSegmentFinder - Reverse Engineering Documentation

## Executive Summary
Implements `SegmentFinder` to identify Grapheme Cluster boundaries. Used for text cursor movement and selection granularity.

## Algorithm
- Uses `TextPaint` to measure width? No, uses `GraphemeBreak.isGraphemeBreak` (native?).
- Logic relies on `GraphemeBreak` class (likely JNI to ICU).

## Java-to-C++ Translation Guide
- **ICU**: Use `ubrk_open(UBRK_CHARACTER, ...)` (BreakIterator).
