# CompatOnBackInvokedCallback - Reverse Engineering Documentation

## Executive Summary
`CompatOnBackInvokedCallback` is a marker interface used for backward compatibility. It extends `OnBackInvokedCallback`. Its primary purpose is to distinguish legacy-style callbacks (which might be allowed even if `enableOnBackInvoked` is false in the manifest) from standard system back callbacks.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `interface` extends `OnBackInvokedCallback`
*   **Role**: Marker / Compatibility shim.

## Data Model
No state. Pure interface.

## API Reference
*   `onBackInvoked()`: Inherited from parent, marked `@Override`.

## Java-to-C++ Translation Guide
*   **Inheritance**: `class CompatOnBackInvokedCallback : public OnBackInvokedCallback`.
*   **Usage**: Since it's a marker, C++ code checking `instanceof` (via `dynamic_cast` or generic type checking) will treat this differently than a raw `OnBackInvokedCallback`.

## Implementation Risks
*   None. It's a trivial interface definition.
