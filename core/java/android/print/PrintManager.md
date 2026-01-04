# PrintManager - Reverse Engineering Documentation

## Executive Summary
`PrintManager` is the system service entry point for printing. It provides APIs to start print jobs, manage printers, and observe print services. It handles the IPC with the `print` system service (`IPrintManager`).

## Architecture Overview
- **Pattern**: System Service Manager.
- **IPC**: Wraps `IPrintManager`.
- **Context**: Per-user context aware.

## Detailed Functionality
1.  **Printing**: `print(...)` creates a `PrintDocumentAdapterDelegate` (binder stub) to wrap the app's adapter and passes it to the system service. It handles the UI launch intent.
2.  **Job Management**: `getPrintJobs`, `cancelPrintJob`, `restartPrintJob`.
3.  **Discovery**: `createPrinterDiscoverySession` factories a session object.
4.  **Listeners**: Manages listeners for job state (`PrintJobStateChangeListener`), services, and recommendations. Wraps them in binder stubs (`*Wrapper` inner classes) to pass to the system.

## Data Model
-   **Inner Classes**:
    -   `PrintDocumentAdapterDelegate`: The crucial bridge between the local `PrintDocumentAdapter` and the remote system. It handles lifecycle events and marshals calls to the main thread `Handler`.
    -   `*Wrapper` classes: WeakReference-holding Binder stubs for listeners to avoid leaks.

## API Reference
-   `print(String, PrintDocumentAdapter, PrintAttributes)`
-   `getPrintJobs()`
-   `getGlobalPrintManagerForUser(int)` (Internal)

## Java-to-C++ Translation Guide
-   **Delegate Logic**: The `PrintDocumentAdapterDelegate` is the most complex part. It must implement the `IPrintDocumentAdapter` AIDL interface and safely dispatch calls to the provided C++ adapter implementation, likely involving a thread loop or message queue to match the main-thread requirement of the Java API.
-   **Binder Wrappers**: Implementing the `Stub` classes for listeners.
