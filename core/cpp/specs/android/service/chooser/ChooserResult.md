# ChooserResult - Reverse Engineering Documentation

## Executive Summary
`ChooserResult` is a Parcelable sent to a caller-supplied `IntentSender` to report the outcome of a system chooser session (e.g., user selected an app, copied to clipboard, or edited).

## Data Model

### Fields
*   `mType`: `int` - The type of result (SELECTED_COMPONENT, COPY, EDIT, UNKNOWN).
*   `mSelectedComponent`: `ComponentName` - The selected activity (only if type is SELECTED_COMPONENT).
*   `mIsShortcut`: `boolean` - True if the selection was a Direct Share shortcut.

### Constants
*   `CHOOSER_RESULT_UNKNOWN`, `SELECTED_COMPONENT`, `COPY`, `EDIT`.

## API Reference

### Getters
*   `getType()`
*   `getSelectedComponent()`
*   `isShortcut()`

## Java-to-C++ Translation Guide

### Parcelable
*   **Java**: Standard `Parcelable`.
*   **C++**: `android::Parcelable`.

## Implementation Notes
*   **Immutable**.
