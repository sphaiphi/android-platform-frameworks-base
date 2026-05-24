# PromptContentViewParcelable - Reverse Engineering Documentation

## Executive Summary
`PromptContentViewParcelable` is a sealed interface combining `PromptContentView` and `Parcelable`.

## Architecture Overview
Restricts implementations to `PromptVerticalListContentView` and `PromptContentViewWithMoreOptionsButton`.

## Java-to-C++ Translation Guide
- **Polymorphism**: Base class for content view parcelables.
