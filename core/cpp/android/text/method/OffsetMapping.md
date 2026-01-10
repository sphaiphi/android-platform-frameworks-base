# OffsetMapping - Reverse Engineering Documentation

## Executive Summary
Interface for mapping offsets between an original string and a transformed string (e.g., when a TransformationMethod inserts/deletes text).

## API Reference
- **`originalToTransformed(int offset, int strategy)`**
- **`transformedToOriginal(int offset, int strategy)`**

## Java-to-C++ Translation Guide
- **Coordinate Conversion**: Essential for editing text that is visually transformed (like password dots or formatted numbers).
