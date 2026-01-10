# DataShareWriteAdapter - Reverse Engineering Documentation

## Executive Summary
Interface for apps to handle writing data during a data share session.

## Methods
*   `onWrite(ParcelFileDescriptor)`.
*   `onRejected`, `onError`.

## Java-to-C++ Translation Guide
*   **Callback Interface**: Abstract class / std::function.
