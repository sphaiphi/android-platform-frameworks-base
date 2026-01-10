# AccessibilityRequestPreparer - Reverse Engineering Documentation

## Executive Summary
An abstract class used to handle synchronous accessibility requests that might require async preparation. It allows a View to be notified *before* a request (like `addExtraDataToAccessibilityNodeInfo`) is processed, giving it time to fetch data.

## Workflow
1.  Register preparer with `AccessibilityManager`.
2.  System requests data.
3.  `onPrepareExtraData` is called.
4.  Preparer does work and sends the `preparationFinishedMessage`.

## Java-to-C++ Translation Guide
*   **Messaging**: Relies on Android `Message` passing.
