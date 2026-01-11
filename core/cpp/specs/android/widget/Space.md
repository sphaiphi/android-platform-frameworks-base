# Space - Reverse Engineering Documentation

## Executive Summary
`Space` is a lightweight, invisible `View` used to create gaps between components in layouts. It performs no drawing and has no interaction.

## Architecture Overview
*   **Inheritance**: `View` -> `Space`.
*   **Optimization**: Overrides `draw()` to do nothing.

## Detailed Functionality
*   **Measurement**: `onMeasure` respects the width/height specs to reserve space in the parent layout.
*   **Visibility**: Sets itself to `INVISIBLE` (or effectively so) to avoid overhead.

## Java-to-C++ Translation Guide
*   **Implementation**: Trivial. A View that measures but doesn't draw.

## Implementation Risks
*   None.
