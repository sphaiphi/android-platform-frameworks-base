# InputContentInfo - Reverse Engineering Documentation

## Executive Summary
Container for content (like images/stickers) sent from IME to Editor via `commitContent`. Handles permission granting for URIs.

## Data Model
*   `mContentUri`: Uri.
*   `mDescription`: ClipDescription (MIME types).
*   `mLinkUri`: Optional web link.

## Java-to-C++ Translation Guide
*   **Parcelable**: Standard serialization.
*   **Permissions**: Uri permission logic is Android specific.
