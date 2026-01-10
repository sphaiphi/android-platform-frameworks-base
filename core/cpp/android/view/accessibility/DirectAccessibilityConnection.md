# DirectAccessibilityConnection - Reverse Engineering Documentation

## Executive Summary
A specialized implementation of `IAccessibilityServiceConnection` used for in-process accessibility queries. Instead of IPC to system_server, it talks directly to the local `ViewRootImpl`'s `AccessibilityInteractionController`.

## Purpose
Used when an app process (e.g., via `AccessibilityManager` or UI automation) wants to query its own UI without the round-trip overhead or when operating in a restricted context.

## Java-to-C++ Translation Guide
*   **Interface**: Implements an AIDL interface (`IAccessibilityServiceConnection`).
