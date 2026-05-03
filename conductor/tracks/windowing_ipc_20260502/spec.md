# Specification - Core Windowing IPC (IWindowSession)

## Overview
This track implements the foundational IPC layer between the application's `ViewRootImpl` and the system's Window Manager Service using the `IWindowSession` interface. By replacing existing mocks in `ViewRootImpl.cpp`, this track enables actual window registration, layout negotiation, and the retrieval of native `Surface` objects for rendering.

## Functional Requirements
- **Window Registration**: Implement `addToDisplay()` to allow `ViewRootImpl` to register a new window instance with the system.
- **Layout Negotiation**: Implement `relayout()` to negotiate window dimensions and insets, and critically, to retrieve the `Surface` handle from the system.
- **Rendering Synchronization**: Implement `finishDrawing()` to notify the system when a frame has been rendered and is ready for composition.
- **ViewRootImpl Integration**: Update the `ViewRootImpl` class to utilize the real `IWindowSession` implementation instead of hardcoded mocks.

## Non-Functional Requirements
- **Error Handling**: Utilize `std::expected` for type-safe, recoverable error reporting in all IPC methods, aligning with project architectural patterns.
- **Modern C++**: Adhere strictly to C++23 standards and NDK r29 best practices.
- **IPC Efficiency**: Minimize overhead in the `relayout` loop to ensure smooth UI performance.

## Acceptance Criteria
1. **Surface Retrieval**: A call to `relayout()` successfully returns a valid, non-null `Surface` object that can be used for drawing.
2. **Focus Management**: The window can successfully request and receive input focus through the session.
3. **Registration Flow**: `ViewRootImpl` can successfully complete a full `addToDisplay` -> `relayout` -> `finishDrawing` cycle without errors.

## Out of Scope
- Implementation of secondary `IWindowSession` methods (e.g., wallpaper offsets, drag-and-drop, display hash generation).
- Full implementation of `IWindowManager` (focused only on the session layer for now).
