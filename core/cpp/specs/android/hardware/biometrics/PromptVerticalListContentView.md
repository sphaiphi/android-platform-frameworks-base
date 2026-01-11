# PromptVerticalListContentView - Reverse Engineering Documentation

## Executive Summary
`PromptVerticalListContentView` defines a content view template that displays a vertical list of items (plain text or bulleted text).

## Detailed Functionality
- **Data**: `mContentList` (List of items), `mDescription`.
- **Limits**:
    - Max items: 20.
    - Max chars per item: 640.
    - Max chars description: 225.

## Java-to-C++ Translation Guide
- **Struct**: `struct { std::string description; std::vector<PromptContentItem> items; }`.
- **Validation**: Enforce limits if constructing this object in C++.

## Implementation Risks
- Deeply nested parcelables (View -> List -> Items).
