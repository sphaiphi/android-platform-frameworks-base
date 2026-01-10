# Text - Reverse Engineering Documentation

## Executive Summary
`Text` wraps a `CharSequence` with truncation configuration. It is the primitive for all textual content in Smartspace templates.

## Architecture Overview
- **Package**: `android.app.smartspace.uitemplatedata`
- **Type**: `Parcelable`.
- **Dependency**: `android.text.TextUtils.TruncateAt`.

## Detailed Functionality
- **Content**: `mText` (CharSequence).
- **Ellipsis**: `mTruncateAtType` (START, MIDDLE, END, MARQUEE).
- **Layout**: `mMaxLines` (Integer).

### Serialization
- Writes Text (CharSequence), TruncateAt (String name), MaxLines (Int).

## Data Model

| Field | Type | Description |
|-------|------|-------------|
| `mText` | `CharSequence` | Content. |
| `mTruncateAtType` | `TruncateAt` | Ellipsis mode. |
| `mMaxLines` | `int` | Line limit. |

## Java-to-C++ Translation Guide
- **Enum**: `TextUtils.TruncateAt` needs a C++ enum equivalent.
- **Serialization**: `TruncateAt` is serialized as a String (`name()`). C++ must read the string and map back to an enum.

## Test Cases & Validation
- **Defaults**: Builder defaults to `END` truncation and 1 max line.
