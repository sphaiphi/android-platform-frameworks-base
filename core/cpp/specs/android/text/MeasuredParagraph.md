# MeasuredParagraph - Reverse Engineering Documentation

## Executive Summary
Holds measurement information for a single paragraph, including text, Bidi levels, and character widths. Used to cache layout information.

## Data Model
- **`mCopiedBuffer`**: char array of the text.
- **`mLevels`**: Bidi levels per character.
- **`mWidths`**: Widths per character.
- **`mMeasuredText`**: Pointer to native `MeasuredText` object (Minikin).

## API Reference
- **`buildForBidi`**: Computes Bidi only.
- **`buildForMeasurement`**: Computes widths.
- **`buildForStaticLayout`**: Computes everything needed for line breaking (native).
- **`getDirections`**: Returns `Layout.Directions`.

## Java-to-C++ Translation Guide
- **Native Wrapper**: This class wraps native objects. The C++ framework will likely use the native `MeasuredText` class directly.
