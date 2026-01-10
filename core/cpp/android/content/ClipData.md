# ClipData - Reverse Engineering Documentation

## Executive Summary
`ClipData` represents the data on the clipboard. It handles complex data types including text, intents, and URIs. It holds a list of `Item`s and a `ClipDescription` metadata object.

## Architecture Overview
- **Inheritance:** Implements `Parcelable`.
- **Components:** Contains `ClipDescription`, `Bitmap` (icon), and `ArrayList<Item>`.

## Detailed Functionality

### `Item` (Inner Class)
**Purpose**: Holds a single unit of data (Text, HTML, Intent, URI).
**Coercion**:
- `coerceToText(Context)`: Converts contents to `CharSequence`. Handles resolving URIs to streams if necessary.
- `coerceToHtmlText(Context)`: Converts to HTML.

### `prepareToLeaveProcess(boolean)`
**Purpose**: Fixes Uris and grants permissions before sending data to another process.
**Algorithm**: StrictMode checks on file URIs.

### Constructors / Factory Methods
- `newPlainText`, `newHtmlText`, `newIntent`, `newUri` helper methods ensure correct MIME types are set in `ClipDescription`.

## Data Model
- `mClipDescription`: `ClipDescription`.
- `mIcon`: `Bitmap` (optional).
- `mItems`: `ArrayList<Item>`.

## API Reference
- `public static ClipData newPlainText(CharSequence label, CharSequence text)`
- `public void addItem(Item item)`
- `public Item getItemAt(int index)`
- `public String toString()`

## Java-to-C++ Translation Guide
- **Parceling**: `ClipData` is heavily parceled. The C++ implementation must match the parcel format exactly to be compatible with Java services.
- **URI Handling**: `Item` relies on `ContentResolver` to coerce URIs to text. In C++, interacting with Content Providers requires `IContentProvider`.

## Implementation Risks
- **MIME Types**: Maintaining sync between the items and the description's MIME types is manual in some methods (`addItem` vs `addItem(resolver)`).
- **Security**: URI permission grants (`FLAG_GRANT_READ_URI_PERMISSION`) are implicitly handled during parceling/intent sending in Java. C++ needs to handle this mechanism.
