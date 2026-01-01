# InlineSuggestionSession - Reverse Engineering Documentation

## Executive Summary
`InlineSuggestionSession` represents a single lifecycle of a request for Inline Suggestions (autofill appearing in the keyboard). It handles the flow: Request from Autofill -> Call to IME -> IME creates request -> Response from Autofill -> IME renders response.

## Architecture Overview
*   **Role**: Session state machine.
*   **Thread Safety**: Main thread only.

## Detailed Functionality

### Lifecycle
*   **Creation**: Created when Autofill service requests inline suggestions.
*   **`makeInlineSuggestionRequestUncheck()`**:
    *   Calls `mRequestSupplier` (IME's implementation) to create `InlineSuggestionsRequest`.
    *   Registers `InlineSuggestionsResponseCallbackImpl`.
    *   Calls `mCallback.onInlineSuggestionsRequest` to send request to Autofill.
*   **Response Handling**:
    *   `handleOnInlineSuggestionsResponse`: Received from Autofill. Checks controller match. Consumes response via `mResponseConsumer` (passed to IME to render).
*   **Invalidation**: Cleans up callbacks.

### Callback (`InlineSuggestionsResponseCallbackImpl`)
*   Stub implementation passed to Autofill. Receives responses and posts them to main thread.

## Data Model
*   `mRequestInfo`: Info about the request.
*   `mCallback`: Interface to Autofill.
*   `mResponseConsumer`: Lambda to render suggestions.

## Java-to-C++ Translation Guide
*   **Logic**: Standard state machine.
*   **Binder**: Interactions with `IInlineSuggestionsRequestCallback`.

## Implementation Risks
*   **Lifecycle Mismatch**: Autofill session vs IME session. Session must be invalidated if IME finishes input.
