# PrecomputedText - Reverse Engineering Documentation

## Executive Summary
Represents text where layout measurements (Bidi, widths, line breaks) have been computed in advance, potentially on a background thread.

## Data Model
- **`mText`**: Original `Spannable`.
- **`mParams`**: Parameters used for measurement (Paint, break strategy, etc.).
- **`mParagraphInfo`**: Array of `ParagraphInfo` (holding `MeasuredParagraph`s).

## API Reference
- **`create(CharSequence, Params)`**: Computes metrics and returns `PrecomputedText`.
- **`checkResultUsable`**: Checks if params match.

## Java-to-C++ Translation Guide
- **Optimization**: Allows separating measure from layout. In C++, this would involve creating `MeasuredText` objects and holding them.
