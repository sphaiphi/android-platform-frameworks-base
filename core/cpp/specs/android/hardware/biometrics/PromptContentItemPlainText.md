# PromptContentItemPlainText - Reverse Engineering Documentation

## Executive Summary
`PromptContentItemPlainText` represents a plain text line in a `BiometricPrompt`.

## Detailed Functionality
- Wraps a `String mText`.
- Implements Parcelable.

## Java-to-C++ Translation Guide
- **Struct**: `struct PromptContentItemPlainText { std::string text; };`
