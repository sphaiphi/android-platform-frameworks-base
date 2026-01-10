# FragmentController - Reverse Engineering Documentation

## Executive Summary
`FragmentController` exposes `FragmentManager` functionality to a host (like `Activity`). It delegates lifecycle events from the host to the `FragmentManager`.

## Architecture Overview
*   **Dependency**: `FragmentHostCallback`.
*   **Role**: Proxy/Facade.

## Detailed Functionality
*   **Lifecycle Dispatch**: `dispatchCreate`, `dispatchResume`, `dispatchDestroy`, etc. Calls corresponding methods on `FragmentManager`.
*   **State Management**: `saveAllState`, `restoreAllState`.
*   **Loaders**: `doLoaderStart`, `doLoaderStop`.

## Java-to-C++ Translation Guide
*   Pass-through class.

## Implementation Risks
*   None.
