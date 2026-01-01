# UriCodec.java - Reverse Engineering Documentation

## Executive Summary
`UriCodec` provides logic to decode "application/x-www-form-urlencoded" content, specifically handling percent-encoding (`%xx`) and optional `+` to space conversion.

## Architecture Overview
- **Type**: Utility Class
- **Package**: `android.net`
- **Usage**: Used by `Uri` to decode query parameters and other components.

## Algorithm
1.  Iterate string characters.
2.  If `%`, read next 2 chars, parse as hex, append byte.
3.  If `+` AND `convertPlus` is true, append space.
4.  Else, append char.
5.  Accumulated bytes are decoded using the specified `Charset` (UTF-8 typically). Replaces invalid sequences with `\ufffd`.

## Java-to-C++ Translation Guide
Standard URL decoding.
-   Be careful with Charset decoding. Java's `CharsetDecoder` handles multi-byte UTF-8 sequences. C++ string handling often treats strings as raw bytes. Explicit UTF-8 decoding logic (e.g., using ICU or a lightweight UTF-8 library) is needed to handle malformed input gracefully if strict adherence to `\ufffd` replacement is required.
