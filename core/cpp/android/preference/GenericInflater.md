# GenericInflater - Reverse Engineering Documentation

## Executive Summary
`GenericInflater` is a generic abstract class for inflating XML resource files into object hierarchies. It forms the basis for `PreferenceInflater`.

**Note:** This class is deprecated and hidden.

## Architecture Overview
- **Generics**: `T` (Item type), `P` (Parent type).
- **Mechanism**: Uses `XmlPullParser` to parse XML and reflection (`Constructor`) to instantiate classes based on tag names.

## Detailed Functionality
1.  **Factory Pattern**: Supports a `Factory` interface to customize item creation.
2.  **Inflation Loop**: Recursively descends the XML tree (`rInflate`), creating items (`createItem`) and adding them to parents (`addItemFromInflater`).
3.  **Reflection**: Caches constructors to optimize instantiation speed.

## API Reference
-   `inflate(int, P)`: Inflate from resource ID.
-   `inflate(XmlPullParser, P)`: Inflate from parser.
-   `createItem(...)`: Instantiates a class by name.

## Java-to-C++ Translation Guide
-   **Reflection**: C++ lacks Java-style reflection. XML tag names must be mapped to C++ class constructors via a factory registry or map.
-   **XML Parsing**: Use a C++ XML parser (e.g., libxml2, tinyxml).

## Implementation Risks
-   **Type Safety**: Heavily relies on casting.
-   **Reflection**: The core mechanism is reflection-based; a static alternative is required for C++.
