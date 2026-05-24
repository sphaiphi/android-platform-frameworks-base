# WebMessagePort - Reverse Engineering Documentation

## Executive Summary
`WebMessagePort` represents one endpoint of an HTML5 Message Channel. It allows two-way communication with JavaScript.

## Detailed Functionality
*   **`postMessage(WebMessage)`**: Sends a message to the entangled port.
*   **`close()`**: Closes the port.
*   **`setWebMessageCallback()`**: Sets the listener for incoming messages.

## Java-to-C++ Translation Guide
*   **MessagePort**: Maps to the internal `MessagePort` implementation in the browser engine.
*   **Entanglement**: Handles the entanglement logic where ports are pairs.
