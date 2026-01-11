# CharSequenceCharacterIterator - Reverse Engineering Documentation

## Executive Summary
Implements Java's `java.text.CharacterIterator` interface over a `CharSequence`.

## Data Model
- **`mCharSeq`** (`CharSequence`): The data source.
- **`mBeginIndex`, `mEndIndex`**: Bounds.
- **`mIndex`**: Current position.

## API Reference
- Standard `CharacterIterator` methods: `first`, `last`, `current`, `next`, `previous`, `setIndex`.
- **`clone()`**: Shallow copy.

## Java-to-C++ Translation Guide
- **Usage**: Mostly used for ICU interactions where `CharacterIterator` is required.
- **C++**: ICU C++ API usually takes `UChar*` or `UnicodeString`. Adapters might be needed if interfacing with Java-style iterators, but typically C++ uses pointers/iterators.
