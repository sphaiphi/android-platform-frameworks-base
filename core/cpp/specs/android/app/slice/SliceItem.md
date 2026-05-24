# SliceItem - Reverse Engineering Documentation

## Executive Summary
`SliceItem` represents a single unit of content within a `Slice`. It is a polymorphic container that can hold various types of data (Text, Icon, Action, Int, etc.) along with format information and hints.

## Architecture Overview
*   **Package**: `android.app.slice`
*   **Type**: `final class`, implements `Parcelable`
*   **Role**: Node in the `Slice` tree.

## Detailed Functionality

### Polymorphic Content Holder
The class stores a generic `Object mObj` and a `String mFormat` tag. The format dictates the type of `mObj`.

| Format String (`mFormat`) | Underlying Java Type (`mObj`) | Description |
| :--- | :--- | :--- |
| `FORMAT_SLICE` ("slice") | `Slice` | A nested sub-slice. |
| `FORMAT_TEXT` ("text") | `CharSequence` | Text content. |
| `FORMAT_IMAGE` ("image") | `Icon` | An image/icon. |
| `FORMAT_ACTION` ("action") | `Pair<PendingIntent, Slice>` | An interactive action wrapping an Intent and a Slice definition for that action. |
| `FORMAT_INT` ("int") | `Integer` | Integer value (color, priority, etc.). |
| `FORMAT_LONG` ("long") | `Long` | Long value (timestamp). |
| `FORMAT_REMOTE_INPUT` ("input")| `RemoteInput` | For text input. |
| `FORMAT_BUNDLE` ("bundle") | `Bundle` | Extensions. |

### Serialization (Parceling)
**Algorithm**:
1.  Write Hints (`String[]`).
2.  Write Format (`String`).
3.  Write SubType (`String`).
4.  Write Object (`mObj`) based on Format logic:
    *   Switch on `getBaseType(format)`.
    *   Delegate to specific `writeToParcel` for Slice, Icon, RemoteInput, Bundle, PendingIntent.
    *   `FORMAT_ACTION`: Writes both the `PendingIntent` and the `Slice`.
    *   `FORMAT_TEXT`: Uses `TextUtils.writeToParcel`.
    *   `FORMAT_INT/LONG`: Writes primitive.

**Java-Specific Notes**:
*   `FORMAT_ACTION` logic splits the Pair into two writes.
*   `getBaseType` handles subtypes (though standard types don't usually use slashes, the check exists: `index = type.indexOf('/')`).

## Data Model

### `SliceItem`
| Field | Type | Description |
| :--- | :--- | :--- |
| `mHints` | `String[]` | Contextual hints. |
| `mFormat` | `String` | Type discriminator. |
| `mSubType` | `String` | Additional type info (e.g., "source", "message", "color"). |
| `mObj` | `Object` | The actual data payload. |

## API Reference

### Getters
*   `getFormat()`, `getSubType()`, `getHints()`.
*   Typed getters cast `mObj`:
    *   `getText()` -> `CharSequence`
    *   `getIcon()` -> `Icon`
    *   `getAction()` -> `PendingIntent` (extracts from Pair)
    *   `getSlice()` -> `Slice` (Handling `FORMAT_ACTION` returns the second part of Pair, `FORMAT_SLICE` returns `mObj`).
    *   `getInt()`, `getLong()`.

### `hasHint(String hint)`
*   Checks presence in `mHints` array using `ArrayUtils.contains`.

### `hasHints(String[] hints)`
*   Returns `true` if **all** provided hints are present (except empty strings).

### `hasAnyHints(String[] hints)`
*   Returns `true` if **any** provided hint is present.

## Java-to-C++ Translation Guide

### Handling `mObj` Polymorphism
C++ does not have a generic `Object` root class. Use `std::variant` or a tagged union.
**Suggested Structure**:
```cpp
struct SliceItem {
    std::vector<std::string> hints;
    std::string format;
    std::string subType;
    
    using Payload = std::variant<
        std::shared_ptr<Slice>,
        std::string, // Text
        std::shared_ptr<Icon>,
        std::pair<std::shared_ptr<PendingIntent>, std::shared_ptr<Slice>>, // Action
        int32_t,
        int64_t,
        std::shared_ptr<RemoteInput>,
        std::shared_ptr<Bundle>
    >;
    Payload obj;
};
```

### Parceling
Implement a manual switch-case for reading/writing the variant based on the `format` string, mirroring the Java `writeObj`/`readObj`.

## Test Cases & Validation

### Case 1: Action Item
*   **Input**: Create Item with `FORMAT_ACTION`, `PendingIntent` P, `Slice` S.
*   **Check**: `getAction()` returns P, `getSlice()` returns S.
*   **Serialization**: Verify P and S are written sequentially.

### Case 2: SubType
*   **Input**: Create Int Item with `SUBTYPE_COLOR`.
*   **Check**: `getInt()` returns value, `getSubType()` returns "color".

## Implementation Risks
*   **Type Safety**: Java casts at runtime. C++ `std::get` will throw if the variant holds the wrong type. The C++ implementation of getters must check `mFormat` before accessing the variant to avoid crashes (or use `std::get_if`).
*   **Format String**: Relying on string comparison for types is brittle but required for compatibility.

## Questions for C++ Team
*   Do we have `Icon`, `PendingIntent`, `RemoteInput` implementations in C++? If not, these parts of `SliceItem` cannot be fully implemented.
