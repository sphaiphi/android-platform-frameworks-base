# EntityIterator - Reverse Engineering Documentation

## Executive Summary
`EntityIterator` extends `Iterator<Entity>` to provide `reset()` and `close()` methods. It is used for iterating over `Entity` objects, typically wrapping a Cursor.

## Architecture Overview
-   **Inheritance:** Extends `Iterator<Entity>`.

## API Reference
-   `void reset()`
-   `void close()`

## Java-to-C++ Translation Guide
-   **Iterator Pattern**: As with `CursorEntityIterator`, maps to a custom iterator or reader class in C++.

## Implementation Risks
-   **Resource Management**: `close()` must be called to release the underlying cursor.
