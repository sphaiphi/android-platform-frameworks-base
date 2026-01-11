# EditTextPreference - Reverse Engineering Documentation

## Executive Summary
`EditTextPreference` is a dialog-based preference that shows an `EditText` field, allowing the user to enter a string value.

**Note:** This class is deprecated.

## Architecture Overview
- **Inheritance**: `EditTextPreference` -> `DialogPreference`.
- **Storage**: Persists a `String` value.

## Detailed Functionality
- **Dialog Content**: displays an `EditText` inside the dialog.
- **Persistence**: Saves the text to SharedPreferences when the dialog is closed with a positive result.
- **Binding**: Updates the `EditText` content when the dialog opens.

## Data Model
- **Value**: `String`.

## API Reference
- `setText(String)`: Sets and persists the value.
- `getText()`: Returns the current value.
- `getEditText()`: Accessor for the underlying widget.

## Java-to-C++ Translation Guide
- **EditText**: Map to a text input field in the target C++ UI.
- **Persistence**: Use `persistString`.

## Implementation Risks
-   **Input Handling**: Needs to handle IME (keyboard) showing automatically when dialog opens.
