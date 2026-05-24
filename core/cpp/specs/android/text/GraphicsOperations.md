# GraphicsOperations - Reverse Engineering Documentation

## Executive Summary
Interface for `CharSequence`s that can perform drawing and measuring operations internally (optimization). Implemented by `SpannableStringBuilder`.

## API Reference
- `drawText`, `drawTextRun`, `measureText`, `getTextWidths`, `getTextRunAdvances`, `getTextRunCursor`.

## Java-to-C++ Translation Guide
- **Design**: In C++, text objects usually don't draw themselves. This pattern might be refactored into the Rendering/Canvas layer rather than the String layer.
