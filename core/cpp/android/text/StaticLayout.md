# StaticLayout - Reverse Engineering Documentation

## Executive Summary
Layout for immutable text. It breaks text into lines and calculates positions once.

## Architecture
- Uses `LineBreaker` (native) for the heavy lifting of line breaking (hyphenation, justification).
- Stores result in `mLines` (packed int array) and `mLineDirections`.

## Data Model
- **`mLines`**: Packed array storing start, top, descent, hyphenation, ellipsis info for each line.
- **`mLineDirections`**: Array of `Directions`.

## Key Algorithms
- **`generate`**:
    1. Measures text (using `MeasuredParagraph`).
    2. Feeds text and constraints to `LineBreaker`.
    3. Receives break points.
    4. Populates `mLines`.

## Java-to-C++ Translation Guide
- **Native Integration**: The Java code is mostly a wrapper preparing data for `LineBreaker` (native). C++ implementation will use `LineBreaker` directly.
- **Storage**: `mLines` packing format is specific to Android's Java view system (to save object overhead). C++ might use structs.
