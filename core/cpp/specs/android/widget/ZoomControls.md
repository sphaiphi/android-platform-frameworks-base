# ZoomControls - Reverse Engineering Documentation

## Executive Summary
`ZoomControls` is a `LinearLayout` containing two `ZoomButton`s (In and Out).

## Architecture Overview
*   **Inheritance**: `LinearLayout` -> `ZoomControls`.
*   **Status**: Deprecated.

## Detailed Functionality
*   **Composition**: Inflates a layout with two buttons.
*   **Callbacks**: `setOnZoomInClickListener`, `setOnZoomOutClickListener`.

## Java-to-C++ Translation Guide
*   **Composite Widget**: Simple container.

## Implementation Risks
*   None.
