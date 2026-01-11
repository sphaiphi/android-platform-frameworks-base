# WireTypeMismatchException - Reverse Engineering Documentation

## Executive Summary
Specific exception thrown by `ProtoInputStream` when the wire type read from the stream doesn't match the expected wire type for the requested field type (e.g., calling `readInt` on a length-delimited field).

## Java-to-C++ Translation Guide
*   **Exception**: Subclass of the parse exception.
