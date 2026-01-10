# HandwritingGesture - Reverse Engineering Documentation

## Executive Summary
Base class for all stylus handwriting gestures.

## Data Model
*   `mType`: Gesture type ID (SELECT, INSERT, DELETE, etc.).
*   `mFallbackText`: Text to commit if gesture fails.

## Java-to-C++ Translation Guide
*   **Polymorphism**: Base class for hierarchy.
