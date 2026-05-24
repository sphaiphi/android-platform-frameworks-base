# CutoutSpecification - Reverse Engineering Documentation

## Executive Summary
`CutoutSpecification` is a utility class responsible for parsing a string-based specification (usually from resources) that describes the geometry and placement of display cutouts (notches). It converts a specialized SVG-like path string into `Path` objects and `Rect` bounds used by the windowing system.

## Architecture Overview
*   **Role**: Geometry parser for display notches.
*   **Format**: Uses a custom BNF-defined string format combining SVG paths with markers like `@left`, `@right`, `@bottom`, and `@dp`.
*   **Coordinate System**: Translates paths from a normalized space to physical display coordinates.

## Detailed Functionality

### 1. Parsing Logic (`Parser`)
*   **Markers**: Identifies keywords to determine which edge of the screen a cutout belongs to.
*   **Scaling**: Handles `@dp` marker to scale coordinates based on display density.
*   **Matrix Transformation**: Applies rotations and translations to position the SVG path at the correct screen edge.

### 2. Inset Calculation
*   **Safe Insets**: Automatically determines the "safe area" (non-functional area) for each edge based on the parsed bounds.

## Java-to-C++ Translation Guide
*   **Path Parsing**: Use `android::PathParser` (native) to convert SVG path strings.
*   **Geometry**: Heavily relies on `android::Matrix` and `android::Rect`.

## Implementation Risks
*   **Parsing Errors**: Invalid specification strings can lead to incorrect safe insets, causing UI elements to be obscured by the physical notch.
*   **Precision**: Rounding errors during the conversion from float-based SVG paths to integer-based `Rect` bounds can cause 1-pixel misalignments.
