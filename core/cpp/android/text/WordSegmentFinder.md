# WordSegmentFinder - Reverse Engineering Documentation

## Executive Summary
Implements `SegmentFinder` using `WordIterator` (ICU) to find word start/end boundaries.

## Java-to-C++ Translation Guide
- **ICU**: Use `BreakIterator` (Word instance).
