# NumberKeyListener - Reverse Engineering Documentation

## Executive Summary
Base class for numeric key listeners. Filters input based on a set of accepted characters.

## API Reference
- **`getAcceptedChars()`**: Abstract.
- **`filter`**: Rejects characters not in the accepted set.
- **`onKeyDown`**: Handles typing. Replaces text if a valid char is typed.

## Java-to-C++ Translation Guide
- **Base Logic**: Common filtering logic.
