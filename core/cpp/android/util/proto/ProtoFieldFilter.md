# ProtoFieldFilter - Reverse Engineering Documentation

## Executive Summary
A utility to filter fields from a raw Protobuf stream. It reads an input stream and writes to an output stream, copying only fields that match a given predicate.

## Logic
*   **Loop**: Reads tags (varints).
*   **Predicate**: `mFieldPredicate.test(fieldNumber)`.
*   **Copy/Skip**:
    *   If true: Copies tag and data (`copyFieldData`).
    *   If false: Skips data (`skipFieldData`).
*   **Data Types**: Handles Varint, Fixed64, LengthDelimited, Fixed32.

## Java-to-C++ Translation Guide
*   **Streaming**: Standard stream processing pattern.
