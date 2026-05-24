# ConfigurationController - Reverse Engineering Documentation

## Executive Summary
`ConfigurationController` handles configuration updates within `ActivityThread`. It manages the pending configuration, compatibility overrides, and applies updates to resources and components (Activities, etc.).

## Architecture Overview
*   **Dependencies**: `ActivityThreadInternal`, `ResourcesManager`.
*   **State**: `mPendingConfiguration`, `mConfiguration`, `mCompatConfiguration`.

## Detailed Functionality
*   **Update Logic**:
    1.  Compares new config with current.
    2.  Updates `ResourcesManager`.
    3.  Updates default density / `Bitmap`.
    4.  Applies compatibility overrides (screen density).
    5.  Dispatches `onConfigurationChanged` to registered `ComponentCallbacks2` (Applications, Services, ContentProviders).
*   **Handling**: `handleConfigurationChanged`.

## Java-to-C++ Translation Guide
*   **Core Logic**: Logic for diffing configurations and dispatching callbacks.
*   **Resource Integration**: Tight coupling with `ResourcesManager`.

## Implementation Risks
*   **Resource Consistency**: Ensuring all `Resources` objects in the process are updated atomically or consistently is complex.
