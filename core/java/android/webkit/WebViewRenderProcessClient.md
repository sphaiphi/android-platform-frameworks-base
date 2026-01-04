# WebViewRenderProcessClient - Reverse Engineering Documentation

## Executive Summary
`WebViewRenderProcessClient` receives callbacks about the health of the renderer process (unresponsive/responsive).

## Detailed Functionality
*   **`onRenderProcessUnresponsive`**: Called when the renderer hangs (JS loop, etc.).
*   **`onRenderProcessResponsive`**: Called when it recovers.

## Java-to-C++ Translation Guide
*   **Health Monitor**: The browser engine monitors heartbeat signals from the renderer and dispatches these events.
