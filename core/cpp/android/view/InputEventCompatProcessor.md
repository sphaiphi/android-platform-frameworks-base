# InputEventCompatProcessor - Reverse Engineering Documentation

## Executive Summary
`InputEventCompatProcessor` provides compatibility adjustments for `InputEvent`s before they are delivered to an application and after they are processed. It handles platform-specific quirks and provides specialized logic for features like Stylus buttons and Letterboxed app scrolling.

## Architecture Overview
*   **Role**: Input event compatibility decorator.
*   **Integration**: Used within the `ViewRootImpl` input pipeline.
*   **Target SDK**: Uses the application's target SDK version to decide which compatibility rules to apply.

## Detailed Functionality

### 1. Stylus Compatibility
*   **`processStylusButtonCompatibility()`**: For apps targeting older Android versions (pre-M), it maps the new `BUTTON_STYLUS_PRIMARY` flags to legacy mouse button flags to ensure existing apps can handle stylus buttons.

### 2. Letterbox Scrolling
*   **`processLetterboxScrollCompatibility()`**: Delegates to `LetterboxScrollProcessor` to handle touch events occurring in the letterbox area (black bars) of an app, ensuring they are correctly forwarded to the app's coordinate space.

## Java-to-C++ Translation Guide
*   **Logic**: Primarily conditional checks on flags and SDK versions.
*   **Event Generation**: Note that this class can return a *list* of events, potentially generating new events (like a synthetic `ACTION_DOWN` for scrolling).

## Implementation Risks
*   **Event ID Collisions**: If the processor generates new events, it must ensure their IDs are unique and correctly tracked for cleanup.
