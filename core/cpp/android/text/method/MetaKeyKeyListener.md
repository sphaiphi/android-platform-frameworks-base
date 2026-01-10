# MetaKeyKeyListener - Reverse Engineering Documentation

## Executive Summary
Tracks state of meta keys (Shift, Alt, Sym) within the text buffer using spans (`CAP`, `ALT`, `SYM`). Handles locking/latching of modifiers.

## Data Model
- **Spans**: `CAP`, `ALT`, `SYM`, `SELECTING` (NoCopySpan markers).
- **States**: `PRESSED` (1), `RELEASED` (2), `USED` (3), `LOCKED` (4).

## API Reference
- **`getMetaState`**: Returns integer bitmask of active meta keys.
- **`adjustMetaAfterKeypress`**: Updates state (e.g. PRESSED -> USED).
- **`handleKeyDown/Up`**: Updates state based on key events.

## Java-to-C++ Translation Guide
- **State Machine**: Critical for correct keyboard behavior (especially virtual/soft keyboards or hardware keyboards with sticky modifiers).
