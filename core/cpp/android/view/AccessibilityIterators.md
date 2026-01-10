# AccessibilityIterators - Reverse Engineering Documentation

## Executive Summary
`AccessibilityIterators` provides a set of utility classes for iterating through text content based on different granularities (character, word, paragraph). These iterators are essential for accessibility services (like TalkBack) to allow users to navigate through text element by element.

## Architecture Overview
*   **Role**: Text segmentation utility.
*   **Standard Library Usage**: Leverages `java.text.BreakIterator` for locale-aware text boundaries.
*   **Lifecycle**: Iterators often register as configuration change callbacks to update their locale-specific rules dynamically.

## Detailed Functionality

### 1. Granularities
*   **`CharacterTextSegmentIterator`**: Iterates through individual characters based on Unicode rules.
*   **`WordTextSegmentIterator`**: Iterates through words, identifying alphanumeric sequences.
*   **`ParagraphTextSegmentIterator`**: Iterates through text segments separated by newline (`\n`) characters.

### 2. Key Methods
*   **`following(int offset)`**: Returns the start and end indices of the segment immediately after the given offset.
*   **`preceding(int offset)`**: Returns the start and end indices of the segment immediately before the given offset.

## Java-to-C++ Translation Guide
*   **Implementation**: Use ICU (International Components for Unicode) `BreakIterator` in C++.
*   **Locale Handling**: Ensure the native iterator is re-instantiated or updated when the system locale changes.
*   **Return Type**: Map the `int[]` range to a `std::pair<int, int>` or a custom `struct Range`.

## Implementation Risks
*   **Locale Inconsistency**: If the Java and C++ layers use different Unicode versions or locale databases, text navigation might behave differently across the system.
*   **Performance**: Repeatedly calling `isBoundary` or `following` on large strings should be optimized by caching the `BreakIterator` instance.
