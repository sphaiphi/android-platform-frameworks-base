# SliceSpec - Reverse Engineering Documentation

## Executive Summary
`SliceSpec` defines the versioning and schema type for a Slice. It allows the Slice host and provider to agree on the structural expectations of the content.

## Architecture Overview
*   **Package**: `android.app.slice`
*   **Type**: `final class`, implements `Parcelable`.
*   **Role**: Schema definition / Version tag.

## Detailed Functionality

### Data Structure
*   **Type** (`String`): A namespace/name string (e.g., "androidx.slice.LIST").
*   **Revision** (`int`): A monotonically increasing version number.

### Compatibility Check (`canRender`)
**Purpose**: Determines if a host supporting *this* spec can display a slice built for *candidate* spec.
**Logic**:
```java
return this.type.equals(candidate.type) && this.revision >= candidate.revision;
```
**Implication**: Backward compatibility is assumed. A host at revision 2 can render slices at revision 1 or 2, but not 3.

## Data Model

### `SliceSpec`
| Field | Type | Description |
| :--- | :--- | :--- |
| `mType` | `String` | The unique schema identifier. |
| `mRevision` | `int` | The version. |

## API Reference
*   `getType()`
*   `getRevision()`
*   `canRender(SliceSpec)`

## Java-to-C++ Translation Guide
*   **Struct**: Simple struct with `std::string` and `int`.
*   **Parcelable**: Standard string/int write.

## Test Cases
*   **Compat**:
    *   Host (Type A, Rev 2), Slice (Type A, Rev 1) -> `true`.
    *   Host (Type A, Rev 1), Slice (Type A, Rev 2) -> `false`.
    *   Host (Type A, Rev 2), Slice (Type B, Rev 2) -> `false`.

## Implementation Risks
*   None. Very simple value object.
