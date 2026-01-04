# AbsoluteSizeSpan - Reverse Engineering Documentation

## Executive Summary
Changes the text size to an absolute value.

## Properties
- **`mSize`** (int): Size.
- **`mDip`** (boolean): If true, size is in DIP, else physical pixels.

## Java-to-C++ Translation Guide
- **Painting**: Updates `TextPaint` size.
