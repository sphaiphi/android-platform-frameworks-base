# RemoteInputHistoryItem - Reverse Engineering Documentation

## Executive Summary
`RemoteInputHistoryItem` is a data class used to store individual entries of user input history associated with a `RemoteInput` in a notification. It supports both plain text messages and media messages (with a URI and MIME type). This class allows notifications to display a trail of previous replies even after they have been sent.

## Architecture Overview
- **Structure**:
    - `mText`: The text content or fallback text for media.
    - `mMimeType`: MIME type of the media (if applicable).
    - `mUri`: URI pointing to the media content.
- **Inheritance**: Implements `Parcelable`.

## Detailed Functionality

### Media Support
**Purpose**: Handling non-textual replies.
**Logic**: If an item is a media message, it stores the `mUri` and `mMimeType`. It also requires `mText` as a "backup text" to be displayed when the image cannot be loaded or when URI permissions are missing.

### Construction
**Purpose**: Creating history entries.
- `RemoteInputHistoryItem(CharSequence text)`: Standard text-only entry.
- `RemoteInputHistoryItem(String mimeType, Uri uri, CharSequence backupText)`: Media entry.

## API Reference
- `public CharSequence getText()`: Returns text or fallback.
- `public String getMimeType()`: Returns media type.
- `public Uri getUri()`: Returns media content link.

## Java-to-C++ Translation Guide
- **Data Struct**: Map to a simple C++ `class` with `std::optional` or pointers for the media fields.
- **Icon/URI Handling**: Ensure consistency with how `android::net::Uri` is handled in other native components.
- **Parceling**: Implement `writeToParcel` and `readFromParcel` to match the field ordering in the Java source.

## Implementation Risks
- **Permission Chains**: Like `Person` and `RemoteAction`, history items with URIs require that permissions are properly propagated so that the SystemUI can render them.
- **Memory Management**: If many history items are stored in a notification, the total parcel size can grow. C++ implementation should be efficient.
