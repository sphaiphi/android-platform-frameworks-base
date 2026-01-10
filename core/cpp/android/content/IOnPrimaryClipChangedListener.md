# IOnPrimaryClipChangedListener - Reverse Engineering Documentation

## Executive Summary
`IOnPrimaryClipChangedListener` is an AIDL interface for receiving callbacks when the primary clip on the global clipboard changes.

## Architecture Overview
- **Type:** AIDL Interface (Oneway).
- **Relationship:** Used by `IClipboard` (system service) to notify clients (`ClipboardManager`).

## API Reference
- `void dispatchPrimaryClipChanged()`

## Java-to-C++ Translation Guide
- **AIDL**: C++ generated code from `.aidl`.

## Implementation Risks
- None.
