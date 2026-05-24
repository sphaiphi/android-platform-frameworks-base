# DdmHandle - Reverse Engineering Documentation

## Executive Summary
`DdmHandle` is an abstract base class that extends `org.apache.harmony.dalvik.ddmc.ChunkHandler`. It serves as a utility layer for specific DDM (Dalvik Debug Monitor) chunk handlers, providing shared helper methods for serializing and deserializing String data to and from `java.nio.ByteBuffer`.

## Architecture Overview
- **Inheritance**: `DdmHandle` extends `ChunkHandler` (part of the Dalvik runtime DDM support).
- **Role**: It acts as a parent class for specific handlers (e.g., `DdmHandleHello`, `DdmHandleHeap`) but does not register any chunk types itself.
- **Dependencies**: Relies on `java.nio.ByteBuffer` for data manipulation.

## Detailed Functionality

### `getString`
**Purpose**: Reads a string from a `ByteBuffer`.
**Algorithm**:
1.  Allocates a `char` array of the specified length.
2.  Iterates `len` times, reading a `char` (2 bytes) from the buffer for each iteration.
3.  Constructs and returns a new `String` from the character array.
**Java-Specific Notes**: Assumes 16-bit characters (UTF-16BE/LE depending on buffer order, though DDM usually uses big-endian).
**C++ Implementation Guidance**: Ensure the ByteBuffer reading matches the endianness of the stream. DDM chunks are typically Big-Endian.

### `putString`
**Purpose**: Writes a string into a `ByteBuffer`.
**Algorithm**:
1.  Iterates through the characters of the input string.
2.  Writes each character (2 bytes) into the buffer.
**C++ Implementation Guidance**: Write string characters as 16-bit integers.

## Data Model
This class does not maintain state.

## API Reference

| Method | Parameters | Returns | Description |
|--------|------------|---------|-------------|
| `getString` | `ByteBuffer buf`, `int len` | `String` | Reads a string of `len` characters from the buffer. |
| `putString` | `ByteBuffer buf`, `String str` | `void` | Writes the string characters to the buffer. |

## Java-to-C++ Translation Guide

### String Handling
Java uses UTF-16 for internal string representation. The wire format here is raw 16-bit characters.
- **Java**: `buf.getChar()` reads 2 bytes.
- **C++**: Read 2 bytes, handling endianness. Convert to `std::string` (UTF-8) or `std::u16string` depending on internal requirements.

### ByteBuffer
- **Java**: `java.nio.ByteBuffer` handles position and limit.
- **C++**: Use a span or a pointer + size wrapper. Ensure bounds checking.

## Questions for C++ Team
- Is there a shared utility library for DDM chunk parsing in the C++ codebase? These helpers should likely belong there.
