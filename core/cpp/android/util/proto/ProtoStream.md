# ProtoStream - Reverse Engineering Documentation

## Executive Summary
Base class containing constants and enums for Protobuf wire format (Wire Types, Field Types, Field Counts, Shifts/Masks).

## Data Model
*   **Wire Types**: `WIRE_TYPE_VARINT`, `WIRE_TYPE_FIXED64`, etc.
*   **Field Types**: `FIELD_TYPE_DOUBLE`, `FIELD_TYPE_STRING`, etc.
*   **Token Layout**: Defines how `token` (for nested objects) is packed (tag size, repeated flag, depth, object ID, offset).

## Java-to-C++ Translation Guide
*   **Constants**: These map directly to `enums` or `constexpr` values in C++.
*   **Macros/Helpers**: The bitwise operations for ID generation (`makeFieldId`, `makeToken`) are candidate for inline functions.
