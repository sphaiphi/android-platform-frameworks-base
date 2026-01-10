# EditorInfo - Reverse Engineering Documentation

## Executive Summary
Describes an editor (TextView) to an IME. Contains input type, IME options, package name, initial text/selection, and supported handwriting gestures.

## Data Model
*   **Input Type**: `inputType` (flags for class, variation, flags).
*   **Options**: `imeOptions` (actions like Go, Next, Done).
*   **Context**: `packageName`, `fieldId`, `autofillId`.
*   **Initial State**: `initialSelStart`, `initialSelEnd`, `mInitialSurroundingText` (SurroundingText).
*   **Handwriting**: Supported gesture flags.

## Key Algorithms
*   **`makeCompatible`**: Adjusts input type flags for older target SDKs.
*   **`trimLongSurroundingText`**: Truncates initial text if it exceeds memory limits (2KB), preserving selection and context.

## Java-to-C++ Translation Guide
*   **Bitmasks**: Heavy use of bit flags.
*   **Parcelable**: Standard serialization.
