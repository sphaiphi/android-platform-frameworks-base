# RenderProcessGoneDetail - Reverse Engineering Documentation

## Executive Summary
`RenderProcessGoneDetail` provides details when the `WebView`'s renderer process exits unexpectedly. Passed to `WebViewClient#onRenderProcessGone`.

## Detailed Functionality
*   **`didCrash()`**: Returns `true` if it was a crash (segfault/exception), `false` if killed by the system (OOM).
*   **`rendererPriorityAtExit()`**: Returns the priority level of the renderer when it died.

## Java-to-C++ Translation Guide
*   **Process Monitoring**: The browser process monitors child renderer processes. When a pipe closes or a signal is received, this object is constructed to inform the Java layer.
