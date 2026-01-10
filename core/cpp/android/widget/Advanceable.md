# Advanceable - Reverse Engineering Documentation

## Executive Summary
`Advanceable` is a simple interface used primarily by `AppWidgetHost` to interact with collection-type widgets (like `AdapterViewFlipper` or `StackView`). It allows the host to manually advance the view to the next item.

## Architecture Overview
*   **Type**: Interface.
*   **Methods**:
    *   `advance()`: Moves to the next view.
    *   `fyiWillBeAdvancedByHostKThx()`: Notification that the host will handle auto-advancing, so the widget should disable its own internal auto-advance logic.

## Java-to-C++ Translation Guide
*   **Interface**: Pure virtual abstract class.

## Implementation Risks
*   None.
