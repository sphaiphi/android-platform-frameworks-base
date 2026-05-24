# PrintDocumentAdapter - Reverse Engineering Documentation

## Executive Summary
`PrintDocumentAdapter` is the abstract base class that applications must implement to provide printable content. It defines the lifecycle of a print job from the application's perspective, handling layout (sizing) and writing (rendering).

## Architecture Overview
- **Role**: Contract / Callback Interface.
- **Threading**: Methods are invoked on the main thread, but work (layout/write) should be offloaded.
- **Callbacks**: Uses inner callback classes (`LayoutResultCallback`, `WriteResultCallback`) to report completion asynchronously.

## Detailed Functionality
1.  **`onStart()`**: Called once at the beginning.
2.  **`onLayout(...)`**: Called when print attributes change (e.g., user changes paper size). App must calculate page count and report `PrintDocumentInfo`.
3.  **`onWrite(...)`**: Called to render specific pages into a `ParcelFileDescriptor` (usually a PDF file).
4.  **`onFinish()`**: Called at the end.

## Data Model
-   **Callbacks**: Abstract classes extended by the system (and by `PrintDocumentAdapterDelegate`) to receive results.

## API Reference
-   `onLayout(oldAttrs, newAttrs, signal, callback, extras)`
-   `onWrite(pages, destination, signal, callback)`
-   `onStart()`, `onFinish()`

## Java-to-C++ Translation Guide
-   **Abstract Base Class**: Pure virtual functions in C++.
-   **Callbacks**: C++ callback interfaces or `std::function`.
-   **File Descriptor**: `ParcelFileDescriptor` maps to a file descriptor `int`.
-   **Cancellation**: `CancellationSignal` needs a C++ equivalent (e.g., `ICancellationSignal` binder wrapper).
