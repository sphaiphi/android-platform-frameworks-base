# VisibilityPropagation - Reverse Engineering Documentation

## Executive Summary
Base class for propagations that depend on visibility and view center (e.g., Circular, Side).

## Logic
-   **`captureValues`**: Captures `PROPNAME_VISIBILITY` and `PROPNAME_VIEW_CENTER` (calculated from screen location + translation + dimensions).
-   **`getViewX/Y`**: Helper accessors.

## Java-to-C++ Translation Guide
-   **Helper**: Base logic for extracting spatial data.
