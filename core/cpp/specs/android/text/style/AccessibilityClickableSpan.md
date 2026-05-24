# AccessibilityClickableSpan - Reverse Engineering Documentation

## Executive Summary
A placeholder span used when passing `ClickableSpan`s to accessibility services (since `ClickableSpan` is not Parcelable). Allows the service to trigger the click action via IPC.

## Properties
- **`mOriginalClickableSpanId`**: ID to find the original span in the app process.

## Java-to-C++ Translation Guide
- **IPC**: Accessibility mechanism.
