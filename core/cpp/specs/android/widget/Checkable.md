# Checkable - Reverse Engineering Documentation

## Executive Summary
`Checkable` is an interface that defines the behavior for objects that can be toggled between checked and unchecked states.

## Architecture Overview
*   **Type**: Interface.
*   **Methods**:
    *   `setChecked(boolean)`
    *   `isChecked()`
    *   `toggle()`

## Java-to-C++ Translation Guide
*   **Interface**: Pure virtual abstract class. Used by `ListView` to manage selection modes (e.g., `CheckedTextView`).

## Implementation Risks
*   None.
