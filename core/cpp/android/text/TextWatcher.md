# TextWatcher - Reverse Engineering Documentation

## Executive Summary
Interface for listening to changes in an `Editable`.

## API Reference
- **`beforeTextChanged`**: Called before change.
- **`onTextChanged`**: Called during/after change (text replaced).
- **`afterTextChanged`**: Called after change is committed.

## Java-to-C++ Translation Guide
- **Observer**: Standard observer pattern.
