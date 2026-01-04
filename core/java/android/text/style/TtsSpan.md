# TtsSpan - Reverse Engineering Documentation

## Executive Summary
Metadata for Text-To-Speech engines (e.g., "read '123' as digits" vs "cardinal number").

## Data Model
- **`mType`**: Type (cardinal, ordinal, date, etc.).
- **`mArgs`**: PersistableBundle of arguments.

## Java-to-C++ Translation Guide
- **Accessibility**: Passed to TTS services.
