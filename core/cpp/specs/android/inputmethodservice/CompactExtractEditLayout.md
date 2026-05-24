# CompactExtractEditLayout - Reverse Engineering Documentation

## Executive Summary
`CompactExtractEditLayout` is a specialized `LinearLayout` used for the "extracted text" view (the fullscreen editing mode) specifically on small screens (sub 250dp). It calculates its layout dimensions (height, margins, padding) as fractions of the screen size to ensure usability on restricted displays.

## Architecture Overview
*   **Inheritance**: `LinearLayout` -> `CompactExtractEditLayout`.
*   **Role**: View Group logic for layout and positioning.

## Detailed Functionality

### Initialization (`onFinishInflate`)
*   Locates child views by ID:
    *   `inputExtractEditText`
    *   `inputExtractAccessories`
    *   `inputExtractAction`
*   Sets a flag `mPerformLayoutChanges` if all children are found.

### Layout Logic (`applyProportionalLayout`)
*   **Trigger**: `onAttachedToWindow` (if children exist).
*   **Inputs**: Screen width and height pixels.
*   **Calculations**:
    *   **Height**: Fraction of screen height (resource `input_extract_layout_height`).
    *   **Padding**: Fraction of screen width (resources `input_extract_layout_padding_left`, `_right`).
    *   **Margins**: Bottom margins for EditText and Accessories as fraction of screen height.
*   **Screen Roundness**: If screen is round, gravity is set to `BOTTOM`.
*   **Special Handling**: If `isScreenRound` and `height < width` (chin detected), treats height as width to maintain aspect ratio safety.

## Data Model
*   `mInputExtractEditText`, `mInputExtractAccessories`, `mInputExtractAction`: Child Views.
*   `mPerformLayoutChanges`: Boolean flag.

## Java-to-C++ Translation Guide
*   **View Group**: Maps to a custom UI view group in C++.
*   **Resources**: Need access to fraction resources (`getFraction`).
*   **Configuration**: Need access to `Configuration.isScreenRound`.
*   **Layout Params**: Manipulation of `ViewGroup.LayoutParams` and `MarginLayoutParams`.

## Test Cases & Validation
*   **Small Screen**: Verify layout height matches specified fraction of screen height.
*   **Round Screen**: Verify Gravity is BOTTOM.
*   **Missing Children**: Ensure no crash if IDs are missing.
