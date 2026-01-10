# TextClassificationSession - Reverse Engineering Documentation

## Executive Summary
A session-aware wrapper around a `TextClassifier`. It handles generating Session IDs, tracking event lifecycles (via `SelectionEventHelper`), and sanitizing events before passing them to the delegate classifier.

## Architecture
*   **Delegate**: Wraps a real `TextClassifier` (e.g., SystemTextClassifier).
*   **Helper**: `SelectionEventHelper` manages state consistency for selection events.
*   **Cleaner**: Uses `sun.misc.Cleaner` to ensure `destroy()` is called.

## Java-to-C++ Translation Guide
*   **Proxy/Decorator**: Decorates the `TextClassifier` interface.
*   **Destruction**: RAII or explicit destroy.
