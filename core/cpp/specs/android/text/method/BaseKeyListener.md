# BaseKeyListener - Reverse Engineering Documentation

## Executive Summary
Base class for key listeners. Handles `DEL` (Backspace) and `FORWARD_DEL`.

## Key Logic
- **`backspace`**:
    - Deletes selection if present.
    - Or deletes character before cursor.
    - Handles complex deletions (Emoji sequences, Variation Selectors, Surrogate pairs).
- **`forwardDelete`**: Deletes character after cursor.

## Java-to-C++ Translation Guide
- **Complex Deletion**: The state machine in `getOffsetForBackspaceKey` is critical for correctly deleting emoji sequences (e.g., Family emoji) as a single unit. This requires Unicode property checks.
