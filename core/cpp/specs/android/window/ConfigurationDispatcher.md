# ConfigurationDispatcher - Reverse Engineering Documentation

## Executive Summary
`ConfigurationDispatcher` is an interface definition for components (like `Context` implementations) that can propagate `Configuration` updates from the system server to registered listeners (`ComponentCallbacks`).

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `interface`
*   **Role**: Contract for configuration propagation.

## API Reference

### Methods
*   `void dispatchConfigurationChanged(@NonNull Configuration configuration)`: Called when a configuration update occurs.
*   `default boolean shouldReportPrivateChanges()`: Returns `false` by default. Indicates if the dispatcher should report changes even if they are not "public" (i.e., `diffPublicOnly` would normally exclude them).

## Java-to-C++ Translation Guide
*   **Interface**: `class IConfigurationDispatcher` (abstract base class).
*   **Usage**: Used by `WindowTokenClient` or similar update receivers to notify the holding context.

## Implementation Risks
*   None. Simple interface.
