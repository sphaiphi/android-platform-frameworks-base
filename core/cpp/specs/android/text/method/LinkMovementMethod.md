# LinkMovementMethod - Reverse Engineering Documentation

## Executive Summary
Handles movement over and clicking of `ClickableSpan`s (links).

## Functionality
- **Clicking**: Handles `DPAD_CENTER`, `ENTER`, and Touch `UP` events to invoke `ClickableSpan.onClick`.
- **Selection**: Manages selection highlight when a link is focused/touched.

## Java-to-C++ Translation Guide
- **Hit Testing**: Uses `Layout` to map x,y coordinates to text offset and find overlapping spans.
