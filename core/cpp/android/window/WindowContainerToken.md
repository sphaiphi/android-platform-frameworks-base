# WindowContainerToken - Reverse Engineering Documentation

## Executive Summary
`WindowContainerToken` is a Parcelable identity object used to uniquely identify a `WindowContainer` (like a Task or DisplayArea) in the `WindowManager`. It wraps the `IWindowContainerToken` binder interface.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `final class` implements `Parcelable`
*   **Role**: Unique Handle / Identity.

## Detailed Functionality
*   **Encapsulation**: Wraps `IWindowContainerToken` (AIDL).
*   **Equality**: Based on the binder identity.

## Java-to-C++ Translation Guide
*   **Type**: `class WindowContainerToken`.
*   **Member**: `sp<IWindowContainerToken> mRealToken`.

## Implementation Risks
*   None. Standard identity token.
