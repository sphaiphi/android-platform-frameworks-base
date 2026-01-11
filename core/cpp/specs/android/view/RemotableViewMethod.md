# RemotableViewMethod - Reverse Engineering Documentation

## Executive Summary
`RemotableViewMethod` is a runtime annotation used to mark methods on `View` subclasses that are safe and intended to be invoked remotely via the `RemoteViews` mechanism (commonly used for Widgets and Notifications).

## Architecture Overview
*   **Role**: Security and Capability metadata.
*   **Target**: Applied to methods like `setVisibility` or `setText`.

## Detailed Functionality
*   **`asyncImpl`**: Optionally specifies an alternative method name that can be executed on a background thread to improve responsiveness.

## Java-to-C++ Translation Guide
*   **Mapping**: Since C++ lacks standard runtime annotations, this would be implemented as a static "White-list" of method identifiers in the RPC/IPC layer.

## Implementation Risks
*   **Security**: Only methods explicitly marked with this annotation (or equivalent) should be reachable via `RemoteViews` to prevent unauthorized state manipulation.
