# InsertModeTransformationMethod - Reverse Engineering Documentation

## Executive Summary
Transformation method for "Insert Mode" (handwriting). Inserts a placeholder string at a specific offset and highlights the range.

## Data Model
- **`mStart`, `mEnd`**: Highlight range.
- **`mOldTransformationMethod`**: Wraps an existing transformation.

## Java-to-C++ Translation Guide
- **Decoration**: Logic to insert placeholder and manage span indices.
