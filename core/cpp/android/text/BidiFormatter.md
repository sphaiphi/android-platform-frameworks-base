# BidiFormatter - Reverse Engineering Documentation

## Executive Summary
`BidiFormatter` is a utility for handling text directionality when inserting text of potentially unknown direction into a context of specific directionality (e.g., inserting Hebrew text into an English sentence). It uses Unicode control characters (LRM, RLM, LRE, RLE, PDF) to isolate and format the text.

## Data Model
- **`mIsRtlContext`** (`boolean`): Directionality of the context.
- **`mFlags`** (`int`): Options (e.g., `FLAG_STEREO_RESET`).
- **`mDefaultTextDirectionHeuristic`** (`TextDirectionHeuristic`): Algorithm to estimate text direction.

## API Reference
- **`getInstance(...)`**: Factory methods.
- **`unicodeWrap(String str, ...)`**: Wraps the string.
    - Estimates direction of `str`.
    - If direction differs from context, wraps with embedding codes (RLE/LRE ... PDF).
    - Can inject "reset" marks (LRM/RLM) before/after to prevent "stickiness" of neutral characters.
- **`isRtl(String str)`**: Checks directionality.

## Inner Class: `DirectionalityEstimator`
- Scans text to determine entry and exit directionality to decide if reset marks are needed.
- Handles HTML tags (skips them) if configured.

## Java-to-C++ Translation Guide
- **Logic**: The wrapping logic and the `DirectionalityEstimator` state machine need to be ported.
- **Constants**: Define Unicode constants (LRE `0x202A`, etc.).
- **Heuristics**: Depends on `TextDirectionHeuristic` (likely ICU-based in C++).
