# OnReceiveContentListener - Reverse Engineering Documentation

## Executive Summary
`OnReceiveContentListener` is a high-level interface for handling the insertion of rich content (text, images, videos) into a `View`. it provides a unified way for applications to process data coming from the Clipboard, Drag & Drop, or the Soft Keyboard.

## Detailed Functionality
*   **`onReceiveContent()`**: The primary callback. It receives a `ContentInfo` payload.
*   **Delegation**: If the listener doesn't handle certain types of content, it returns them, allowing the system to fall back to default behavior (e.g., standard text insertion).

## Java-to-C++ Translation Guide
*   **Interface**: Define as a virtual base class in C++.
*   **Payload**: Wrap the native `ClipData` equivalent.

## Implementation Risks
*   **Permission Management**: Listeners must be careful to handle URI permissions correctly, especially if processing data asynchronously.
