# CheckedTextView - Reverse Engineering Documentation

## Executive Summary
`CheckedTextView` is a `TextView` that implements `Checkable`. It displays a text label alongside a check mark drawable. It is commonly used as the item view in `ListView`s with `CHOICE_MODE_SINGLE` or `CHOICE_MODE_MULTIPLE`.

## Architecture Overview
*   **Inheritance**: `TextView` -> `CheckedTextView`.
*   **Implements**: `Checkable`.
*   **Components**: `mCheckMarkDrawable`.

## Detailed Functionality

### 1. Check Mark Drawing
*   **`onDraw`**: Draws the `mCheckMarkDrawable` aligned to the left or right (based on `gravity` and RTL).
*   **Padding**: Adjusts the view's padding to make room for the check mark so text doesn't overlap it.

### 2. State Management
*   **`setChecked`**: Updates state, refreshes drawable state (triggering the check mark to change appearance), and notifies accessibility.
*   **`onCreateDrawableState`**: Merges `CHECKED_STATE_SET` into the view's drawable state if checked.

## Java-to-C++ Translation Guide
*   **Layout**: Need to handle the manual layout of the checkmark drawable within the view bounds.
*   **Padding Override**: The class overrides `setPadding` logic to include the checkmark width.

## Implementation Risks
*   **RTL**: Checkmark positioning must respect layout direction.
