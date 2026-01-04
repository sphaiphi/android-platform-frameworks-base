# PrintJob (Service) - Reverse Engineering Documentation

## Executive Summary
This version of `PrintJob` is the service-side representation. It allows the print service to read the job state, inspect the document, and drive the job state machine (start, complete, fail, cancel).

## Architecture Overview
- **Pattern**: State Machine Controller / Proxy.
- **Dependencies**: `IPrintServiceClient`.

## Detailed Functionality
-   **State Transitions**: `start()`, `block()`, `complete()`, `fail()`, `cancel()`. Each method calls the remote service to update the state.
-   **Progress**: `setProgress()`.
-   **Status**: `setStatus()`.
-   **Tagging**: `setTag()` allows services to attach internal string tags to jobs.
-   **Advanced Options**: Access to printer-specific options.

## Data Model
-   `mCachedInfo`: `PrintJobInfo`.
-   `mDocument`: `PrintDocument`.

## API Reference
-   `getId()`, `getInfo()`, `getDocument()`.
-   `start()`, `block()`, `complete()`, `fail()`, `cancel()`.
-   `setProgress()`, `setStatus()`.

## Java-to-C++ Translation Guide
-   **State Logic**: The logic for valid state transitions (e.g., can only `start` if `queued` or `blocked`) is client-side here and must be replicated to prevent invalid IPC calls.
