# ProtoParseException - Reverse Engineering Documentation

## Executive Summary
Runtime exception thrown when parsing invalid protobuf data in `ProtoInputStream` or `EncodedBuffer`.

## Java-to-C++ Translation Guide
*   **Std Exception**: Map to `std::runtime_error` or a specific proto parse error class.
