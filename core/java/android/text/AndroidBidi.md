# AndroidBidi - Reverse Engineering Documentation

## Executive Summary
`AndroidBidi` provides a wrapper around the ICU Bidi implementation (specifically `android.icu.text.Bidi`) to perform the Unicode Bidirectional Algorithm. It is used to determine text directionality (LTR/RTL) and run directions.

## API Reference
- **`bidi(int dir, char[] chs, byte[] chInfo)`**:
    - Runs the Bidi algorithm.
    - `dir`: Request direction (LTR, RTL, Default LTR, Default RTL).
    - `chs`: Input characters.
    - `chInfo`: Output array for Bidi levels.
    - Uses `android.icu.text.Bidi`.
- **`directions(int dir, byte[] levels, int lstart, char[] chars, int cstart, int len)`**:
    - Returns `Layout.Directions` object containing visual runs.
    - Logic processes `levels` array to identify contiguous runs of same directionality.
    - Handles trailing whitespace special cases (visual end vs logical end).
    - Returns `Layout.DIRS_ALL_LEFT_TO_RIGHT` or `Layout.DIRS_ALL_RIGHT_TO_LEFT` for simple cases.

## Java-to-C++ Translation Guide
- **Dependencies**: Depends heavily on ICU4C (`ubidi_...`).
- **Logic**: The `directions` logic manually iterating levels to form runs should be ported carefully to match Android's specific behavior regarding trailing whitespace.
- **Types**: `char[]` -> `char16_t*`, `byte[]` -> `uint8_t*` or `UBiDiLevel*`.
