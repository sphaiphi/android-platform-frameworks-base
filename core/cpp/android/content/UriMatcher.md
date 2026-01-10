# UriMatcher - Reverse Engineering Documentation

## Executive Summary
`UriMatcher` helps match URIs against a set of patterns. It builds a tree structure of URI path segments for efficient matching.

## Architecture Overview
- **Structure:** Tree of `UriMatcher` nodes.

## Detailed Functionality

### `addURI(String authority, String path, int code)`
**Purpose**: Adds a pattern to the matcher.
**Algorithm**:
1. Splits path into tokens.
2. Traverses/Builds the tree.
3. Each node represents a token (Exact match, `#` for number, `*` for text).
4. Sets the code at the leaf node.

### `match(Uri uri)`
**Purpose**: Matches a URI against the tree.
**Algorithm**:
1. Splits URI path.
2. Traverses the tree matching tokens.
3. Returns the code of the matching node, or `NO_MATCH`.

## Data Model
- `mCode`: `int`.
- `mWhich`: `int` (EXACT, NUMBER, TEXT).
- `mText`: `String`.
- `mChildren`: `ArrayList<UriMatcher>`.

## API Reference
- `public void addURI(String authority, String path, int code)`
- `public int match(Uri uri)`

## Java-to-C++ Translation Guide
- **Tree**: N-ary tree structure.
- **String Parsing**: Splitting strings by `/`.

## Implementation Risks
- **Performance**: Tree traversal is efficient, but building it with many patterns consumes memory.