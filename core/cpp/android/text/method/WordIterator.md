# WordIterator - Reverse Engineering Documentation

## Executive Summary
Iterates over word boundaries.

## Functionality
- Uses `BreakIterator.getWordInstance` (ICU).
- Provides `preceding`, `following`, `getBeginning`, `getEnd`.
- Handles punctuation-specific logic (not treated as part of word for some queries).

## Java-to-C++ Translation Guide
- **ICU**: Wrapper around ICU `BreakIterator`. Adds custom logic for punctuation handling.
