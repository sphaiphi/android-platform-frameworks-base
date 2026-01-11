# ListPopupWindow - Reverse Engineering Documentation

## Executive Summary
`ListPopupWindow` is a utility class that manages a popup window containing a `ListView` (`DropDownListView`). It is the core implementation behind `AutoCompleteTextView`, `Spinner` (in dropdown mode), and `PopupMenu`.

## Architecture Overview
*   **Components**:
    *   `PopupWindow`: The floating window container.
    *   `DropDownListView`: The content view.
    *   `PopupDataSetObserver`: Observes the adapter to resize/move the popup.
    *   `ResizePopupRunnable`: Handles auto-resizing.

## Detailed Functionality

### 1. Positioning (`show`)
*   Anchors to a specific `View`.
*   Calculates available screen height to determine if the popup should appear above or below the anchor.
*   Handles vertical/horizontal offsets.

### 2. Sizing (`buildDropDown`)
*   Measures the content width/height.
*   Supports `MATCH_PARENT` or fixed sizes.
*   Restricts height to `getMaxAvailableHeight`.

### 3. Interaction
*   **Modal**: Can be modal (steals focus) or non-modal (allows typing in anchor EditText).
*   **Input Method**: Configures `INPUT_METHOD_NEEDED` or `NOT_NEEDED`.

## Java-to-C++ Translation Guide
*   **Window Management**: Requires a windowing system capable of creating child/popup windows (overlays).
*   **Layout Math**: The positioning logic (collision detection with screen edges) is critical.

## Implementation Risks
*   **Screen Bounds**: Correctly keeping the popup within the display frame while respecting the anchor position.
*   **Focus**: Managing focus between the anchor and the list.
