# Icon - Reverse Engineering Documentation

## Executive Summary
`Icon` is a wrapper around `android.graphics.drawable.Icon` that adds Smartspace-specific metadata like content description (for accessibility) and a tinting flag.

## Architecture Overview
- **Package**: `android.app.smartspace.uitemplatedata`
- **Type**: `Parcelable`.
- **Dependency**: `android.graphics.drawable.Icon`.

## Detailed Functionality

### Data Holding
- `mIcon`: The system Icon object (Bitmap, Resource, URI, etc.).
- `mContentDescription`: Accessibility text.
- `mShouldTint`: Boolean flag (default true).

### Ashmem Optimization
- The Builder calls `mIcon.convertToAshmem()` before building. This is critical for performance when passing large bitmaps across IPC.

### Serialization
- Writes Icon, ContentDescription, Boolean.

## Data Model

| Field | Type | Description |
|-------|------|-------------|
| `mIcon` | `android.graphics.drawable.Icon` | The visual. |
| `mContentDescription` | `CharSequence` | A11y text. |
| `mShouldTint` | `boolean` | Theme coloring. |

## Java-to-C++ Translation Guide
- **Icon**: Requires the C++ equivalent of `android.graphics.drawable.Icon` (likely in `libandroid` or `libgui`).
- **Ashmem**: The C++ implementation must handle the receiving end of an Ashmem-backed icon correctly.

## Test Cases & Validation
1.  **Tint Default**: Verify `mShouldTint` defaults to `true`.
2.  **Ashmem**: Verify bitmaps are transferred via shared memory.
