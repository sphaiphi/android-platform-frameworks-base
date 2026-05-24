# StickyModifierState - Reverse Engineering Documentation

## Executive Summary
`StickyModifierState` is an abstract representation of the state of "Sticky Keys" accessibility feature (whether Shift, Ctrl, Alt, etc. are currently latched or locked).

## Architecture Overview
- **Abstract Class**.
- **States**: "On" (latched, next key consumes it) vs "Locked" (persists until pressed again).

## API Reference
- Methods for each modifier (Shift, Ctrl, Meta, Alt, AltGr):
  - `is...ModifierOn()`
  - `is...ModifierLocked()`

## Data Model
- Implemented by `LocalStickyModifierState` in `InputManagerGlobal` using bitmasks.

## Java-to-C++ Translation Guide
- Bitmask operations on `int32_t`.

## Implementation Risks
- None.
