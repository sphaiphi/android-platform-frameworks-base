# ClipboardManager - Reverse Engineering Documentation

## Executive Summary
`ClipboardManager` is the system service interface for accessing the global clipboard. It allows putting data (`ClipData`) into the clipboard and retrieving it. It also supports listeners for clipboard changes.

## Architecture Overview
- **Inheritance:** Extends `android.text.ClipboardManager` (Legacy compatibility).
- **Service Name:** `Context.CLIPBOARD_SERVICE` ("clipboard").
- **Relationship:** Proxy to `IClipboard` system service.

## Detailed Functionality

### `setPrimaryClip(ClipData clip)`
**Purpose**: Puts data on the clipboard.
**Algorithm**:
1. Validates input.
2. Prepares clip for crossing process boundaries (`prepareToLeaveProcess`).
3. Calls `mService.setPrimaryClip` via IPC.

### `getPrimaryClip()`
**Purpose**: Retrieves data.
**Algorithm**: Calls `mService.getPrimaryClip` via IPC.

### `addPrimaryClipChangedListener` / `removePrimaryClipChangedListener`
**Purpose**: Manages listeners.
**Algorithm**:
- Uses a static `IOnPrimaryClipChangedListener.Stub` (Binder stub) to receive callbacks from the system service.
- Dispatches callbacks to the locally registered Java listeners via a `Handler`.

## Data Model
- `mService`: `IClipboard` - Binder interface to service.
- `mContext`: `Context`.
- `mPrimaryClipChangedListeners`: `ArrayList` of listeners.

## API Reference
- `public void setPrimaryClip(ClipData clip)`
- `public ClipData getPrimaryClip()`
- `public boolean hasPrimaryClip()`
- `public void addPrimaryClipChangedListener(...)`

## Java-to-C++ Translation Guide
- **Service Manager**: `ServiceManager.getService("clipboard")` in Java maps to `defaultServiceManager()->getService(String16("clipboard"))` in C++.
- **Callbacks**: The mechanism of a single Binder stub dispatching to multiple local listeners is a common pattern to reduce IPC tokens.

## Implementation Risks
- **Permission**: Accessing clipboard usually requires focus or user interaction (since Android 10).
- **Large Data**: `ClipData` can contain large bitmaps or URIs. IPC limits apply.
