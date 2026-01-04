# SearchEvent - Reverse Engineering Documentation

## Executive Summary
`SearchEvent` is a simple data class used to encapsulate the details of a hardware or system event that triggers a search request (e.g., pressing a dedicated Search key or button).

## Data Model
*   **`mInputDevice`**: The `InputDevice` that generated the search trigger.

## Detailed Functionality
*   **Context**: Passed to `Window.Callback.onSearchRequested(SearchEvent)` to give the application info about how the search was initiated.

## Java-to-C++ Translation Guide
*   **Structure**: A trivial C++ `class` or `struct` wrapping a pointer to an `InputDevice`.

## Implementation Risks
*   **Null Device**: Ensure the system handles cases where a search is triggered by a source without a defined `InputDevice` (e.g., an accessibility gesture).
