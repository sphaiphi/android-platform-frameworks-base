# Layout - Reverse Engineering Documentation

## Executive Summary
Abstract base class for managing text layout. It handles measuring, line breaking (via subclasses or delegates), and drawing text.

## Core Responsibilities
- **Measuring**: `getDesiredWidth`.
- **Drawing**: `draw`, `drawText`, `drawBackground`.
- **Cursor/Selection**: `getOffsetForHorizontal`, `getPrimaryHorizontal`.
- **Line Info**: `getLineTop`, `getLineStart`, `getLineCount`.

## Data Model
- **`mText`**: The text.
- **`mPaint`**: `TextPaint`.
- **`mWidth`**: Layout width.
- **`mAlignment`**: Text alignment.
- **`mDirections`**: Array of `Directions` (Bidi runs).

## Key Methods
- **`draw`**: Orchestrates drawing of background, text, and highlights.
- **`measure`**: (in `TextLine`) Measures width of runs.
- **`getLineForVertical`**: Binary search to find line index from Y-coordinate.

## Subclasses
- `StaticLayout`: For immutable text.
- `DynamicLayout`: For editable text.
- `BoringLayout`: For simple LTR text.

## Java-to-C++ Translation Guide
- **Core Engine**: This is the heart of the text system. It interfaces with `Minikin` (native font engine).
- **TextLine**: `Layout` uses `TextLine` (recycled) to handle individual line shaping and measuring.
- **Bidi**: Bidi logic is handled here or in `TextLine`.
