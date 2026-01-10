# AutoText - Reverse Engineering Documentation

## Executive Summary
`AutoText` provides a mechanism for retrieving spelling corrections/expansions for frequent misspellings or shortcuts. It loads data from an XML resource into a Trie structure.

## Data Model
- **`mTrie`** (`char[]`): Flattened trie structure.
- **`mText`** (`String`): Storage for the destination strings (replacements).
- **`mLocale`** (`Locale`): Current locale.
- **`mSize`** (`int`): Number of entries.

### Trie Structure (Flattened in `char[]`)
- **Nodes**: Each node consumes 4 chars (`TRIE_SIZEOF`).
    - `TRIE_C` (0): The character to match.
    - `TRIE_OFF` (1): Offset into `mText` for the replacement string (if this node ends a word), or `TRIE_NULL`.
    - `TRIE_CHILD` (2): Index of child node (next char in word).
    - `TRIE_NEXT` (3): Index of sibling node (alternative char at this position).
- **Root**: Index 0.
- **Terminator**: `TRIE_NULL` ((char) -1).

## API Reference
- **`get(CharSequence src, int start, int end, View view)`**: Looks up the substring `src[start, end)` in the trie and returns the replacement string or null. Uses `view` to get context/locale.
- **`getSize(View view)`**: Returns number of entries.

## Algorithm
- **Lookup**: Traverses the `mTrie` array interpreting the flattened nodes.
- **Init**: Parses an XML (format: `<word src="..." dest="..." />`), builds the trie in memory.

## Java-to-C++ Translation Guide
- **Trie**: Reimplement the trie logic. C++ `struct Node { char16_t c; int32_t off; int32_t child; int32_t next; }` packed into an array.
- **Resources**: Needs access to system resources (XML parsing).
- **Locking**: The Java class uses a lock for initialization/swapping instances on locale change. C++ should ensure thread safety.
