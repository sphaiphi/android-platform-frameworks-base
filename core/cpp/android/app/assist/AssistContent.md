# AssistContent - Reverse Engineering Documentation

## Executive Summary
`AssistContent` is a data carrier class used to pass contextual information from an application (`Activity`) to an assistant (like Google Assistant). It contains structured data (JSON-LD), intents, web URIs, clip data, and extras.

## Architecture Overview
- **Type**: Parcelable Data Class.
- **Role**: Context container.
- **Usage**: Filled by `Activity.onProvideAssistContent`, consumed by Assistant services.

## Detailed Functionality

### Content Types
- **Intent**: The intent reflecting the current user action/view.
- **Web URI**: A transportable URI (http/https) representing the content.
- **ClipData**: Additional content items (images, text).
- **Structured Data**: JSON-LD string for semantic understanding.
- **Extras**: `Bundle` for arbitrary data.

### Flags/Booleans
- `mIsAppProvidedIntent`: True if app explicitly set the intent (vs default).
- `mIsAppProvidedWebUri`: True if app explicitly set the web URI.

## Data Model

| Field Name | Java Type | C++ Equivalent Type | Description |
| :--- | :--- | :--- | :--- |
| `mIntent` | `Intent` | `android::content::Intent` | Current activity intent. |
| `mUri` | `Uri` | `android::net::Uri` | Web URI. |
| `mClipData` | `ClipData` | `android::content::ClipData` | Clipboard-style data. |
| `mStructuredData` | `String` | `std::string` | JSON-LD. |
| `mExtras` | `Bundle` | `android::os::Bundle` | Vendor extras. |
| `mIsAppProvidedIntent` | `boolean` | `bool` | Flag. |
| `mIsAppProvidedWebUri` | `boolean` | `bool` | Flag. |

## API Reference
- Setters/Getters for all fields (`setIntent`, `getIntent`, `setWebUri`, etc.).
- `setDefaultIntent`: Logic to set default values from the Activity's main intent.

## Java-to-C++ Translation Guide

### Parcelable Logic
- **Custom Write**: `writeToParcelInternal` manually writes presence flags (`1` or `0`) before writing objects.
- **C++ Implication**: The C++ read/write logic must match this bit-stream exactly. It is **not** just a list of standard parcelables; it has manual `writeInt(1)` guards.

## Test Cases & Validation
- **Defaults**: Check behavior of `setDefaultIntent` (auto-extracts HTTP URI).
- **Serialization**: Verify manual parceling logic (presence flags).

## Implementation Risks
- **Parcel Format**: The manual `if (obj != null) writeInt(1)... else writeInt(0)` pattern is critical. Standard generated C++ parcelables might not match this custom logic without care.
