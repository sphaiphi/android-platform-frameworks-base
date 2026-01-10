# ChooserAction - Reverse Engineering Documentation

## Executive Summary
`ChooserAction` defines a custom action (Icon + Label + PendingIntent) that apps can provide to the system chooser (via `EXTRA_CHOOSER_CUSTOM_ACTIONS`) to appear alongside share targets.

## Data Model

### Fields
*   `mIcon`: `Icon` - Action icon.
*   `mLabel`: `CharSequence` - Action text.
*   `mAction`: `PendingIntent` - Intent to launch when clicked.

## API Reference

### Getters
*   `getIcon()`, `getLabel()`, `getAction()`.

## Java-to-C++ Translation Guide

### Parcelable
*   **Java**: Standard `Parcelable`.
*   **C++**: `android::Parcelable`.

## Implementation Notes
*   **Immutable**.
*   **Builder Pattern**: Used for construction.
