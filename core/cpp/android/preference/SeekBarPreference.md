# SeekBarPreference - Reverse Engineering Documentation

## Executive Summary
`SeekBarPreference` allows the user to select an integer value using a slider (SeekBar) directly in the preference list (inline).

**Note:** This class is deprecated.

## Architecture Overview
- **Inheritance**: `SeekBarPreference` -> `Preference`.
- **Listener**: Implements `OnSeekBarChangeListener`.

## Detailed Functionality
-   **UI**: Displays a `SeekBar` in the widget area.
-   **Interaction**: Updates value as user drags.
-   **Keys**: Handles volume keys to adjust value when focused.
-   **Persistence**: Persists `int` value.

## API Reference
-   `setProgress(int)`, `getProgress()`
-   `setMax(int)`

## Java-to-C++ Translation Guide
-   **Widget**: Inline slider control.
-   **Input**: Key event handling for accessibility/D-pad.
