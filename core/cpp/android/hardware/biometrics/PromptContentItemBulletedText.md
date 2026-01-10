# PromptContentItemBulletedText - Reverse Engineering Documentation

## Executive Summary
`PromptContentItemBulletedText` represents a bulleted list item in a `BiometricPrompt`. It holds a single string.

## Detailed Functionality
- Wraps a `String mText`.
- Implements Parcelable.

## Java-to-C++ Translation Guide
- **Struct**: `struct PromptContentItemBulletedText { std::string text; };`
