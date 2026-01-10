# AccessibilityEventSource - Reverse Engineering Documentation

## Executive Summary
A simple interface defined to be implemented by classes that can be the source of `AccessibilityEvent`s (typically `View`).

## Key Methods
*   `sendAccessibilityEvent(int eventType)`
*   `sendAccessibilityEventUnchecked(AccessibilityEvent event)`

## Java-to-C++ Translation Guide
*   **Interface**: Pure virtual class in C++.
