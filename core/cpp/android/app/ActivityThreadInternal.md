# ActivityThreadInternal - Reverse Engineering Documentation

## Executive Summary
`ActivityThreadInternal` is a package-private interface that defines a subset of `ActivityThread` functionality. It serves as a contract primarily for `ConfigurationController` to interact with the main application thread without exposing the entire `ActivityThread` implementation.

## Architecture Overview
*   **Type**: Interface.
*   **Implementer**: `ActivityThread`.
*   **Consumer**: `ConfigurationController`.

## Detailed Functionality

### Context Access
*   `getSystemContext()`: Retrieve the system `ContextImpl`.
*   `getSystemUiContextNoCreate()`: Retrieve System UI context if available.
*   `getApplication()`: Retrieve the main `Application` object.

### Configuration & Compatibility
*   `isInDensityCompatMode()`: Check if running in density compatibility mode.

### Component Callbacks
*   `collectComponentCallbacks(boolean includeUiContexts)`: Gathers all registered `ComponentCallbacks2` listeners (e.g., for configuration changes or low memory warnings).

## API Reference
*   `ContextImpl getSystemContext()`
*   `Context getSystemUiContextNoCreate()`
*   `boolean isInDensityCompatMode()`
*   `Application getApplication()`
*   `ArrayList<ComponentCallbacks2> collectComponentCallbacks(boolean includeUiContexts)`

## Java-to-C++ Translation Guide

### Interface Definition
*   Define as a pure virtual class (interface) in C++.
    ```cpp
    class ActivityThreadInternal {
    public:
        virtual ~ActivityThreadInternal() = default;
        virtual ContextImpl* getSystemContext() = 0;
        virtual bool isInDensityCompatMode() = 0;
        virtual Application* getApplication() = 0;
        // ...
    };
    ```

### Dependency Injection
*   This interface facilitates dependency injection or decoupling in the C++ architecture, allowing `ConfigurationController` to be testable without a full `ActivityThread`.

## Implementation Risks
*   **Circular Dependencies**: Ensure `ActivityThread` (implementer) and `ConfigurationController` (consumer) do not create reference cycles.
