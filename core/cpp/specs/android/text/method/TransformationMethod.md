# TransformationMethod - Reverse Engineering Documentation

## Executive Summary
Interface for modifying text for display (e.g. password masking).

## API Reference
- **`getTransformation`**: Returns the transformed CharSequence.
- **`onFocusChanged`**: Hook for focus changes.

## Java-to-C++ Translation Guide
- **View Transformation**: Allows `TextView` to display something different from the actual buffer.
