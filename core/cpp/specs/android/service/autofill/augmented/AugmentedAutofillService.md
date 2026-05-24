# AugmentedAutofillService - Reverse Engineering Documentation

## Executive Summary
`AugmentedAutofillService` allows an app to provide autofill suggestions when the standard `AutofillService` fails or is not available. It acts as a fallback or enhancement layer, interacting with the system via an `AutofillProxy` to render its own UI (unlike standard autofill where the system renders the UI).

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC**: Implements `IAugmentedAutofillService.Stub` (anonymous inner class).
*   **Manifest**: Requires `android.permission.BIND_AUGMENTED_AUTOFILL_SERVICE` and action `android.service.autofill.augmented.AugmentedAutofillService`.
*   **Proxy Pattern**: Uses `AutofillProxy` to manage the session state and communicate with the system server.

## Detailed Functionality

### `onBind(Intent intent)`
**Purpose**: Binds the service.
**Returns**: `IAugmentedAutofillService` stub.

### `IAugmentedAutofillService.Stub` Implementation
*   **`onConnected`/`onDisconnected`**: Lifecycle hooks.
*   **`onFillRequest`**: Handles the incoming request from the system.
    *   Creates or reuses an `AutofillProxy`.
    *   Calls the abstract `onFillRequest` with `FillRequest`, `CancellationSignal`, `FillController`, `FillCallback`.
*   **`onDestroyAllFillWindowsRequest`**: Cleans up all active proxies/windows.

### `onFillRequest` (Abstract)
**Purpose**: Process the fill request.
**Parameters**:
*   `request`: `FillRequest` (contains `AutofillProxy`, focused ID, etc.).
*   `controller`: `FillController` (to autofill values).
*   `callback`: `FillCallback` (to return response).

### `AutofillProxy` (Internal Class)
**Purpose**: Manages the connection to the system server (`IAugmentedAutofillManagerClient`) for a specific session.
**Key Methods**:
*   `getSmartSuggestionParams()`: Gets coordinates for the focused view to anchor UI.
*   `autofill()`: Performs the fill operation.
*   `requestShowFillUi()` / `requestHideFillUi()`: Controls UI visibility.
*   `reportResult()`: Sends `FillResponse` back to system (for inline suggestions).

## API Reference

### Methods
*   `requestAutofill(ComponentName, AutofillId)`: Explicitly requests a new autofill session (e.g., if the service thinks it has new data).

## Java-to-C++ Translation Guide

### IPC
*   **Java**: `IAugmentedAutofillService.Stub`
*   **C++**: `BnAugmentedAutofillService`.

### Callback Management
*   **Java**: `AutofillProxy` is complex. It manages the session lifecycle, locks, and communication with `IAugmentedAutofillManagerClient` (Binder proxy to system server).
*   **C++**: Needs a robust `Session` or `Proxy` class to handle the state machine and binder death linking.

### UI Rendering
*   **Java**: `AugmentedAutofillService` differs from standard because *it* can render its own UI (`FillWindow`) or use Inline Suggestions.
*   **C++**: If implementing the UI rendering part, it likely involves `SurfaceControl` or window manager interactions if it's drawing windows, or just passing data for Inline Suggestions.

## Implementation Risks
*   **Concurrency**: Multiple sessions can be active. `mAutofillProxies` is a `SparseArray` that needs synchronized access.
*   **Lifecycle**: Proxies must be destroyed when the session ends or the service unbinds to avoid leaks.
