# PrintDocument - Reverse Engineering Documentation

## Executive Summary
`PrintDocument` represents the document to be printed from the perspective of a `PrintService`. It provides access to the document's metadata (`PrintDocumentInfo`) and its content stream (`ParcelFileDescriptor`).

## Architecture Overview
- **Pattern**: Wrapper / Proxy.
- **IPC**: Uses `IPrintServiceClient` to request the data stream via a pipe.

## Detailed Functionality
-   **Metadata**: `getInfo()` returns `PrintDocumentInfo`.
-   **Data Access**: `getData()` sets up a `ParcelFileDescriptor` pipe (source/sink). It sends the write end (sink) to the system via `writePrintJobData` and returns the read end (source) to the caller.

## API Reference
-   `getInfo()`: Returns metadata.
-   `getData()`: Returns read-side `ParcelFileDescriptor`.

## Java-to-C++ Translation Guide
-   **Pipe**: Use `pipe()` or `socketpair()` logic.
-   **File Descriptors**: Manage ownership of FDs carefully. The returned FD must be closed by the caller.
