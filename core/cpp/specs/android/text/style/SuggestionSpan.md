# SuggestionSpan - Reverse Engineering Documentation

## Executive Summary
Stores suggestions for misspelled words/corrections. Visualized with an underline (wavy/solid).

## Properties
- **`mSuggestions`**: Array of strings.
- **`mFlags`**: Misspelled, Easy Correct, etc.

## Java-to-C++ Translation Guide
- **Painting**: Custom underline drawing in `TextLine` or via `TextPaint` custom underline fields.
