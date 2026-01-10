# ProtoInputStream - Reverse Engineering Documentation

## Executive Summary
Reads Protocol Buffers directly from a stream or byte array without generating code (intermediary objects). Optimized for Android system services.

## Architecture
*   **State Machine**: Tracks current field number, wire type, and nesting depth (`mDepth`).
*   **Buffer**: `byte[] mBuffer` refilled from `InputStream`.
*   **Token Stack**: `mExpectedObjectTokenStack` tracks expected end offsets for nested messages to validate structure.

## Key Algorithms
*   **`nextField`**: Reads the tag (varint). Decodes field number and wire type.
*   **`readInt`, `readLong`, etc.**: Reads value based on requested type. validates wire type.
*   **`start(fieldId)`**: Enters a nested object (length-delimited). Pushes end offset to stack. returns a token.
*   **`end(token)`**: Validates token, ensures all bytes of nested object are consumed (or skips remaining).

## Java-to-C++ Translation Guide
*   **Wire Format**: Standard Protobuf wire format (Varint, Fixed64, LengthDelimited, Fixed32).
*   **Zero-Copy**: C++ can potentially overlay structs or read directly from memory if the proto is flat, but `ProtoInputStream` handles stream logic.
