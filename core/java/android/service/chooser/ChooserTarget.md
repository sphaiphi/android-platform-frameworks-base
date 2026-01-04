# ChooserTarget - Reverse Engineering Documentation

## Executive Summary
`ChooserTarget` represents a specific deep-link target (e.g., a specific chat conversation) returned by a `ChooserTargetService`. **Deprecated**.

## Data Model

### Fields
*   `mTitle`: `CharSequence` - Display title.
*   `mIcon`: `Icon` - Display icon.
*   `mScore`: `float` - Relevance score (0.0 to 1.0).
*   `mComponentName`: `ComponentName` - The activity to handle the intent.
*   `mIntentExtras`: `Bundle` - Extras to merge into the intent.

## API Reference

### Getters
*   `getTitle()`, `getIcon()`, `getScore()`, `getComponentName()`, `getIntentExtras()`.

## Java-to-C++ Translation Guide

### Parcelable
*   **Java**: Standard `Parcelable`.
*   **C++**: `android::Parcelable`.

## Implementation Notes
*   **Immutable**.
*   **Deprecated**.
