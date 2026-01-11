# SectionIndexer - Reverse Engineering Documentation

## Executive Summary
`SectionIndexer` is an interface used by adapters (typically for `ListView` or `GridView`) to allow fast scrolling through sections. It maps between adapter positions and "sections" (e.g., letters of the alphabet).

## Architecture Overview
*   **Type**: Interface.
*   **Methods**:
    *   `Object[] getSections()`: Returns the array of section objects (e.g., `{"A", "B", ...}`).
    *   `int getPositionForSection(int sectionIndex)`: Maps a section index to the starting position in the list.
    *   `int getSectionForPosition(int position)`: Maps a list item position to the section it belongs to.

## Java-to-C++ Translation Guide
*   **Interface**: Pure virtual abstract class.
*   **Usage**: Used by `FastScroller` to draw the preview bubble and jump positions.

## Implementation Risks
*   None.
