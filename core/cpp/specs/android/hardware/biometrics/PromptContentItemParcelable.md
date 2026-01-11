# PromptContentItemParcelable - Reverse Engineering Documentation

## Executive Summary
`PromptContentItemParcelable` is a sealed interface combining `PromptContentItem` and `Parcelable`.

## Architecture Overview
Restricts implementations to `PromptContentItemPlainText` and `PromptContentItemBulletedText`. This ensures type safety when parceling generic content items.

## Java-to-C++ Translation Guide
- **Polymorphism**: Base class for the parcelable hierarchy.
