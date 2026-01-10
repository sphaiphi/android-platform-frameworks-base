# ConfigurationChangedListenerController - Reverse Engineering Documentation

## Executive Summary
`ConfigurationChangedListenerController` manages a list of listeners that want to be notified of configuration changes in `ActivityThread`.

## Architecture Overview
*   **Pattern**: Observer / Listener Container.
*   **Thread Safety**: Synchronized access to listener list.

## Detailed Functionality
*   **Registration**: `addListener`, `removeListener`.
*   **Dispatch**: `dispatchOnConfigurationChanged` iterates listeners and executes callbacks on their associated executors.

## Java-to-C++ Translation Guide
*   `std::vector` of listener structs (callback + executor).
*   Mutex protection.

## Implementation Risks
*   **Reentrancy**: Ensure callbacks don't deadlock if they modify the listener list (though `ArrayList` copy in dispatch handles this).
