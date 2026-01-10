# FillRequest (Augmented) - Reverse Engineering Documentation

## Executive Summary
`FillRequest` (Augmented) represents a request for augmented autofill. It wraps an `AutofillProxy` and allows access to the focused view and inline suggestion requests.

## Data Model

### Fields
*   `mProxy`: `AutofillProxy` - The session controller.
*   `mInlineSuggestionsRequest`: `InlineSuggestionsRequest` - Specs for inline suggestions.

## API Reference

### Getters
*   `getTaskId()`
*   `getActivityComponent()`
*   `getFocusedId()`
*   `getFocusedValue()`
*   `getFocusedViewNode()`
*   `getPresentationParams()`: Gets Smart Suggestion params (coordinates) via Proxy.
*   `getInlineSuggestionsRequest()`

## Java-to-C++ Translation Guide

### Wrapper
*   **Java**: This class is largely a wrapper around `AutofillProxy`.
*   **C++**: Can likely be a light wrapper or a reference to the Session object.

### Dependencies
*   `AutofillProxy` (Internal to Service), `ViewNode`, `AutofillId`, `AutofillValue`.

## Implementation Notes
*   **Proxy Access**: Most methods delegate directly to the `mProxy`.
