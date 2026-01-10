# CancellableHandwritingGesture - Reverse Engineering Documentation

## Executive Summary
Abstract base class for handwriting gestures that can be cancelled (e.g., `InsertModeGesture`). It holds a `CancellationSignal`.

## Data Model
*   `mCancellationSignal`: The signal used to cancel the gesture.
*   `mCancellationSignalToken`: Binder token for cross-process cancellation.

## Java-to-C++ Translation Guide
*   **Inheritance**: Inherits from `HandwritingGesture`.
