# Base64 - Reverse Engineering Documentation

## Executive Summary
Utilities for Base64 encoding and decoding (RFC 2045, RFC 3548). Supports various flags for formatting (padding, wrapping).

## Architecture Overview
*   **Flags**: `DEFAULT`, `NO_PADDING`, `NO_WRAP`, `CRLF`, `URL_SAFE`.
*   **Inner Classes**: `Encoder` and `Decoder` extending abstract `Coder`.

## Key Algorithms
*   **Encoding**:
    *   Maps 3 input bytes to 4 output characters using a lookup table (`ENCODE` or `ENCODE_WEBSAFE`).
    *   Handles tail padding (`=`).
    *   Handles line wrapping (inserting `\n` or `\r\n`).
*   **Decoding**:
    *   Uses a reverse lookup table (`DECODE` or `DECODE_WEBSAFE`).
    *   Ignores whitespace unless strict.
    *   Maps 4 input chars to 3 output bytes.

## Java-to-C++ Translation Guide
*   **Implementation**: There are many C++ Base64 libraries. If implementing from scratch, the lookup table approach is standard.
*   **Memory**: Java allocates output arrays based on `maxOutputSize`. C++ `std::vector<uint8_t>` or `std::string` resizing works similarly.

## Implementation Risks
*   **Security**: Ensure bounds checking on input buffers to avoid overflows.
