# OnBackAnimationCallback - Reverse Engineering Documentation

## Executive Summary
`OnBackAnimationCallback` extends `OnBackInvokedCallback` to provide granular lifecycle events for predictive back animations (start, progress, cancel).

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `interface` extends `OnBackInvokedCallback`
*   **Role**: Listener for back gestures.

## API Reference

### Methods
*   `onBackStarted(@NonNull BackEvent backEvent)`: Called when swipe starts.
*   `onBackProgressed(@NonNull BackEvent backEvent)`: Called during swipe movement.
*   `onBackCancelled()`: Called if swipe is aborted.
*   `onBackInvoked()`: Inherited.

## Java-to-C++ Translation Guide
*   **Interface**: `class OnBackAnimationCallback : public OnBackInvokedCallback`.
*   **Default Methods**: Java interfaces have default empty implementations. C++ pure virtual interface would require implementation, or provide a base adapter class with empty virtuals.

## Implementation Risks
*   None.
