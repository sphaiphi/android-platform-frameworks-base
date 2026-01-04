# TextViewMetrics - Reverse Engineering Documentation

## Executive Summary
`TextViewMetrics` is a utility class defining constants for logging TextView-related metrics (specifically long-press behaviors) to the system.

## Architecture Overview
*   **Type**: Constants Class.
*   **Usage**: Used by `TextView` calls to `MetricsLogger`.

## Constants
*   `SUBTYPE_LONG_PRESS_OTHER`
*   `SUBTYPE_LONG_PRESS_SELECTION`
*   `SUBTYPE_LONG_PRESS_DRAG_AND_DROP`

## Java-to-C++ Translation Guide
*   **Enum**: Convert to an enum or constants namespace.

## Implementation Risks
*   None.
