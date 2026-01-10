# Emoji - Reverse Engineering Documentation

## Executive Summary
Utility class for detecting Emoji characters and properties (modifiers, keycaps, etc.).

## API Reference
- **`isEmoji(int codePoint)`**: Checks `UProperty.EMOJI`.
- **`isEmojiModifier(int codePoint)`**: Checks `UProperty.EMOJI_MODIFIER`.
- **`isKeycapBase(int codePoint)`**: Checks if char can be base of keycap (digits, *, #).
- **`isRegionalIndicatorSymbol(int codePoint)`**: Checks range.

## Java-to-C++ Translation Guide
- **ICU**: Most methods map directly to `u_hasBinaryProperty` in ICU4C.
- **Constants**: Define codepoint ranges/constants.
