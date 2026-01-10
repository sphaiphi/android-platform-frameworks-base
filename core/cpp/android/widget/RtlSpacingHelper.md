# RtlSpacingHelper - Reverse Engineering Documentation

## Executive Summary
`RtlSpacingHelper` is a utility class to manage start/end values and convert them to left/right based on the layout direction. Used by views like `Toolbar` or `TableLayout` to handle padding/margins.

## Architecture Overview
*   **Role**: Math Helper.

## Detailed Functionality
*   **State**: Stores `start`, `end`, `left`, `right`.
*   **Logic**: `setDirection(isRtl)` updates the effective left/right values. Priority is given to start/end if defined.

## Java-to-C++ Translation Guide
*   **Logic**: Simple conditional assignments.

## Implementation Risks
*   None.
