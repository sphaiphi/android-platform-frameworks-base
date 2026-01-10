# BoringLayout - Reverse Engineering Documentation

## Executive Summary
`BoringLayout` is a lightweight implementation of `Layout` optimized for single-line text that is all Left-to-Right (LTR) and requires no complex breaking or complex Bidi processing.

## Architecture
- Extends `Layout`.
- Used by `TextView` for simple labels.

## API Reference
- **`make(...)`**: Factory methods to create instances.
- **`isBoring(CharSequence text, TextPaint paint, ...)`**: Static utility. Checks if text is "boring".
    - Returns `Metrics` if boring, `null` otherwise.
    - Checks for: `\n`, `\t`, Bidi characters, Surrogate pairs (sometimes), `ParagraphStyle` spans.
    - Calculates width if boring.
- **`replaceOrMake(...)`**: Reuses an existing `BoringLayout` or creates a new one.
- **`draw(...)`**: Optimized drawing. Calls `canvas.drawText` directly if no interesting spans/highlights.

## Data Model
- **`mDirect`** (`String`): Stores the text if it's a simple String and alignment is normal. Used for faster drawing.
- **`mTopPadding`, `mBottomPadding`**, `mDesc`, `mBottom**: Metrics cache.

## Java-to-C++ Translation Guide
- **Heuristics**: `isBoring` logic detects characters that trigger complex layout (ICU calls).
- **Optimization**: The core value is avoiding the full `StaticLayout`/`DynamicLayout` engine. In C++, ensures that `Minikin` or the layout engine has a fast path for simple runs.
- **Drawing**: Direct calls to `Canvas::drawText`.

