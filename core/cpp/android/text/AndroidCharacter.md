# AndroidCharacter - Reverse Engineering Documentation

## Executive Summary
`AndroidCharacter` is a deprecated utility class that exposes character properties like East Asian Width, directionality, and mirroring. It acts as a bridge to native implementations or ICU.

## API Reference
- **`getDirectionalities(char[] src, byte[] dest, int count)`**: Native method. Batch retrieval of directionality.
- **`getEastAsianWidth(char input)`**: Native method. Returns one of `EAST_ASIAN_WIDTH_*` constants.
- **`getEastAsianWidths(char[] src, int start, int count, byte[] dest)`**: Native method. Batch retrieval of EAW.
- **`mirror(char[] text, int start, int count)`**: Native method. Applies mirroring to characters in the buffer (e.g. '(' to ')').
- **`getMirror(char ch)`**: Native method. Returns the mirrored char.

## Java-to-C++ Translation Guide
- **Replacement**: This class is largely deprecated in favor of `android.icu.lang.UCharacter`.
- **Implementation**: In C++, use ICU4C functions:
    - Directionality: `u_charDirection`.
    - East Asian Width: `u_getIntPropertyValue(c, UCHAR_EAST_ASIAN_WIDTH)`.
    - Mirroring: `u_charMirror`.
