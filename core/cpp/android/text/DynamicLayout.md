# DynamicLayout - Reverse Engineering Documentation

## Executive Summary
`DynamicLayout` is a text layout that updates itself when the underlying `Editable` text changes. It is used by `EditText`. It reflows text incrementally to avoid full re-layout.

## Architecture
- Extends `Layout`.
- Uses `StaticLayout` internally to reflow ranges of text.
- Observes changes via `ChangeWatcher` (implements `TextWatcher`, `SpanWatcher`).

## Data Model
- **`mBase`** (`CharSequence`): The source text (usually `Editable`).
- **`mDisplay`** (`CharSequence`): The text to display (may be transformed, e.g., password).
- **`mBlockEndLines`** (`int[]`): Stores line numbers ending blocks (for partial redraw/management).
- **`mInts`** (`PackedIntVector`): Stores line data (start, top, descent, etc.). Optimized for insertions/deletions.
- **`mObjects`** (`PackedObjectVector`): Stores per-line objects (like `Directions`).

## Key Algorithms
- **`reflow(CharSequence s, int where, int before, int after)`**:
    1.  Finds the affected paragraph range (expands `where`/`after` to `\n` boundaries).
    2.  Creates a `StaticLayout` for just that range.
    3.  Updates `mInts` and `mObjects` by removing old lines and inserting new lines from the `StaticLayout`.
    4.  Adjusts `TOP` values for subsequent lines.
    5.  Updates block indices.

## Java-to-C++ Translation Guide
- **Complexity**: High. Requires replicating `PackedIntVector` for efficient storage.
- **Incremental Update**: The `reflow` logic is critical. It must efficiently splice new layout results into existing data structures.
- **Dependencies**: Relies on `StaticLayout` for the actual line breaking and measuring of the modified region.
- **Synchronization**: `sLock`, `sStaticLayout` (shared static builder). Thread safety concerns.
