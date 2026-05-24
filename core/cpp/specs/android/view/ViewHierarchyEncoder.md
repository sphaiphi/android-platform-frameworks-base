# ViewHierarchyEncoder - Reverse Engineering Documentation

## Executive Summary
`ViewHierarchyEncoder` is a specialized binary serializer used to export the state of a view tree (and all view properties) to a stream. it is primarily used by developer tools like "Layout Inspector" to efficiently capture the entire UI state for remote debugging.

## Architecture Overview
*   **Role**: Binary UI state serializer.
*   **Format**: Uses a map-based encoding where property names are replaced with short integer IDs to reduce payload size.
*   **Type System**: Supports basic primitives (`Z`, `B`, `S`, `I`, `J`, `F`, `D`), Strings, and nested Maps.

## Detailed Functionality

### 1. Stream Management
*   **`beginObject()`** / **`endObject()`**: Marks the start and end of a view node's properties.
*   **`addProperty()`**: Encodes a key-value pair.
*   **`endStream()`**: Writes the final string table (mapping IDs back to property names) to the end of the stream.

### 2. Performance
*   Optimized for high-frequency property names across multiple views by using a shared property ID map.

## Java-to-C++ Translation Guide
*   **Protocol**: Needs a C++ implementation of the binary encoding spec.
*   **Serialization**: In C++, this can be integrated with `android::uirenderer::RenderNode` to export hardware rendering properties alongside view attributes.

## Implementation Risks
*   **Version Drift**: The binary signature (e.g., `'Z'` for boolean) must be strictly maintained for compatibility with existing desktop debugging tools.
