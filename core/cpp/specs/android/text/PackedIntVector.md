# PackedIntVector - Reverse Engineering Documentation

## Executive Summary
Optimized 2D integer array. It uses a gap buffer strategy for rows to allow efficient insertion and deletion of rows (lines) in `DynamicLayout`.

## Data Model
- **`mValues`**: Flattened array of values.
- **`mRowGapStart`, `mRowGapLength`**: Gap for rows.
- **`mValueGap`**: Array of gaps for each column (handling width changes? No, likely for shifting values).

## API Reference
- **`getValue(int row, int col)`**
- **`setValue(int row, int col, int val)`**
- **`insertAt(int row, int[] values)`**
- **`deleteAt(int row, int count)`**

## Java-to-C++ Translation Guide
- **Gap Buffer**: Implement a gap buffer or use `std::vector` with `insert`/`erase`. Since C++ vectors are contiguous, gap buffers are useful if insertions are localized (like typing).
