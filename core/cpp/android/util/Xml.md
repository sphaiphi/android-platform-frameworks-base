# Xml - Reverse Engineering Documentation

## Executive Summary
Utility class for XML parsing and serialization. Acts as a factory for Pull Parsers and Serializers.

## Architecture Overview
*   **Facades**: Provides static methods to get `XmlPullParser` and `XmlSerializer`.
*   **Implementations**:
    *   `KXmlParser` / `KXmlSerializer` (Default, text-based).
    *   `BinaryXmlPullParser` / `BinaryXmlSerializer` (Binary format for performance).
*   **Encoding**: Supports detection of encoding.

## Key Algorithms
*   **`resolvePullParser`**: Detects if an input stream is binary XML (magic number) or text XML and returns the appropriate parser.
*   **`copy`**: Pipes events from a Parser to a Serializer (useful for format conversion).

## Java-to-C++ Translation Guide
*   **Libraries**: Use `libxml2` or `expat`. Android has a specific binary XML format (ABX) that would need a custom parser/writer in C++.

## Implementation Risks
*   **Binary XML**: The binary format is Android-specific and versioned.
