# FontFamilyUpdateRequest - Reverse Engineering Documentation

## Executive Summary
`FontFamilyUpdateRequest` encapsulates a request to update or add a system font family. It allows specifying both font files (via `FontFileUpdateRequest`) and family definitions (mapping names to styles and axes).

## Architecture Overview
- **Builder Pattern**: Uses nested `Builder` classes for constructing `FontFamily`, `Font`, and the main `FontFamilyUpdateRequest`.
- **Composition**:
    - Contains a list of `FontFileUpdateRequest` (for adding new files).
    - Contains a list of `FontFamily` definitions (for updating configuration).

## Detailed Functionality

### Inner Classes
1.  **`FontFamily`**: Represents a named collection of fonts.
    -   `getName()`: Returns the family name (e.g., "roboto").
    -   `getFonts()`: Returns the list of `Font` objects in this family.
2.  **`Font`**: Represents a specific style/variation within a family.
    -   `getPostScriptName()`: Identifies the font file (OpenType Name ID 6).
    -   `getStyle()`: `FontStyle` (weight, slant).
    -   `getAxes()`: List of `FontVariationAxis` for variable fonts.
    -   `getIndex()`: Font collection index (TTC index).

### Core Logic
-   **Validation**: Builders perform strict null and range checks.
-   **Data Transport**: This object is typically passed to `FontManager.updateFontFamily`.

## Java-to-C++ Translation Guide
-   **Data Structures**: Maps closely to a structured C++ request object.
-   **Validation**: Ensure C++ builders/constructors replicate the `Preconditions` checks.

## Source Reference
Defined in `FontFamilyUpdateRequest.java`.
