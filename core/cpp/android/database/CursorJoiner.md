# CursorJoiner - Reverse Engineering Documentation

## Executive Summary
`CursorJoiner` implements a specialized join operation (like SQL JOIN) between two cursors in memory. It assumes both cursors are *already sorted* by the join columns. It iterates both cursors in parallel to determine if rows match (BOTH), or exist only in left/right (LEFT/RIGHT).

## Architecture Overview
*   **Implements**: `Iterator<Result>`, `Iterable<Result>`.
*   **Algorithm**: Merge Join (Sort-Merge Join step).

## Detailed Functionality

### Initialization
*   Takes `cursorLeft`, `columnNamesLeft`, `cursorRight`, `columnNamesRight`.
*   Builds column indices for comparison.
*   Moves both cursors to first.

### Iteration (`next`)
*   **State Machine**:
    *   Compare columns of current row in Left vs Right.
    *   **Equal**: Result `BOTH`. Increment Left and Right.
    *   **Left < Right**: Result `LEFT`. Increment Left.
    *   **Left > Right**: Result `RIGHT`. Increment Right.
    *   **Left EOF**: Result `RIGHT`. Increment Right.
    *   **Right EOF**: Result `LEFT`. Increment Left.
*   **Comparison**: Uses `String.compareTo`. Handles nulls (nulls compare low).

### Data Model
*   `mCompareResult`: Current state (LEFT, RIGHT, BOTH).
*   `mValues`: String array buffer for current comparison values.

## Java-to-C++ Translation Guide
*   **Comparator**: Must implement string comparison matching Java's (Lexicographical).
*   **Iterator**: C++ iterators are distinct from Java's `hasNext`/`next`. Can implement as a class with `advance()` and `state()`.

## Test Cases
1.  **Matching**: L:[1, 2], R:[1, 2]. -> BOTH, BOTH.
2.  **Gap**: L:[1, 3], R:[1, 2, 3]. -> BOTH, RIGHT (2), BOTH.
3.  **Unique**: L:[1], R:[2]. -> LEFT, RIGHT.
