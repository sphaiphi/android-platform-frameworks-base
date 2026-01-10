# EditorBoundsInfo - Reverse Engineering Documentation

## Executive Summary
Container for editor bounds (the view's visible area) and handwriting bounds (expanded area for stylus input).

## Data Model
*   `mEditorBounds`: `RectF`.
*   `mHandwritingBounds`: `RectF`.

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
