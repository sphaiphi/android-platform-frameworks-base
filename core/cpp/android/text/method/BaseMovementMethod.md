# BaseMovementMethod - Reverse Engineering Documentation

## Executive Summary
Base class for movement methods. Handles generic motion events (scroll wheel).

## API Reference
- **`onKeyDown`, `onKeyOther`**: Dispatches to `handleMovementKey`.
- **`onGenericMotionEvent`**: Handles scroll axis.

## Java-to-C++ Translation Guide
- **Base Class**: Logic for event dispatching.
