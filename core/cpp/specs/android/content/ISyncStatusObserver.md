# ISyncStatusObserver - Reverse Engineering Documentation

## Executive Summary
`ISyncStatusObserver` is a callback interface for receiving notifications about changes in sync status (active, pending, settings).

## Architecture Overview
- **Type:** AIDL Interface (Oneway).
- **Usage:** Registered with `ContentResolver.addStatusChangeListener`.

## API Reference
- `void onStatusChanged(int which)`

## Java-to-C++ Translation Guide
- **AIDL**: C++ generated code.

## Implementation Risks
- None.
