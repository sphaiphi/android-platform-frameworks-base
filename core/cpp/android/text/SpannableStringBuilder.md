# SpannableStringBuilder - Reverse Engineering Documentation

## Executive Summary
The heavy-lifter of mutable text. Implements a gap buffer for text and an interval tree (or similar structure) for spans. Supports text insertion, deletion, replacement, and span attachment/detachment.

## Data Model
- **Text**: `char[] mText`, `mGapStart`, `mGapLength`.
- **Spans**: `Object[] mSpans`, `int[] mSpanStarts`, `int[] mSpanEnds`, `int[] mSpanFlags`.
- **Tree**: `mSpanMax` (interval tree optimization to find overlapping spans).

## Key Algorithms
- **Gap Buffer**: Standard text gap buffer.
- **Span Management**:
    - Spans are stored in arrays.
    - `restoreInvariants()` sorts spans by start.
    - `treeRoot()`, `calcMax()` maintain the interval tree structure used by `getSpans`.
    - `sendToSpanWatchers()`: Notifies watchers of changes.
- **`replace`**: Complex logic to:
    1. Move gap.
    2. Resize buffer.
    3. Update span indices (expand/contract/move).
    4. Remove spans that become empty (if exclusive).
    5. Insert text.
    6. Notify watchers.

## Java-to-C++ Translation Guide
- **Complexity**: High.
- **Data Structures**: Needs efficient text storage (gap buffer or piece table) and spatial index for spans (interval tree).
- **Correctness**: Span behavior (expansion/contraction based on flags) is subtle and critical.
