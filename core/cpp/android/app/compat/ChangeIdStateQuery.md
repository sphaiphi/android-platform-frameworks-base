# ChangeIdStateQuery - Reverse Engineering Documentation

## Executive Summary
`ChangeIdStateQuery` serves as the composite cache key for `ChangeIdStateCache`. It encapsulates the parameters necessary to uniquely identify a query for a compatibility change's state, specifically targeting either a package name or a specific UID.

## Architecture Overview
*   **Type**: Immutable Data Object (Value Object).
*   **Role**: Dictionary/Map Key.
*   **Annotations**: `@Immutable`, `@RavenwoodKeepWholeClass`.

## Detailed Functionality

### Core Purpose
Holds the triplet or quadruplet of data required to ask "Is this change enabled?":
1.  **Change ID**: The unique `long` identifier of the feature flag.
2.  **Type**: Context type (`QUERY_BY_PACKAGE_NAME` or `QUERY_BY_UID`).
3.  **Context**: Either `packageName` + `userId` OR `uid`.

### Creation
Private constructor enforces creation via static factory methods to ensure data consistency based on the `type`.

## Data Model

### Fields
| Name | Type | Description |
| :--- | :--- | :--- |
| `type` | `int` (`@QueryType`) | Discriminator: `0` (Package Name) or `1` (UID). |
| `changeId` | `long` | The compatibility change ID. |
| `packageName` | `String` | Target package name (valid if type is Package Name). |
| `uid` | `int` | Target UID (valid if type is UID). |
| `userId` | `int` | Target User ID (valid if type is Package Name). |

### Static Constants
*   `QUERY_BY_PACKAGE_NAME = 0`
*   `QUERY_BY_UID = 1`

## API Reference

### Factory Methods
*   `static ChangeIdStateQuery byPackageName(long changeId, String packageName, int userId)`
    *   Sets `type = QUERY_BY_PACKAGE_NAME`.
    *   Sets `uid = 0` (unused).
*   `static ChangeIdStateQuery byUid(long changeId, int uid)`
    *   Sets `type = QUERY_BY_UID`.
    *   Sets `packageName = null`, `userId = 0` (unused).

### Standard Methods
*   `equals(Object other)`: Performs deep equality check on all fields.
*   `hashCode()`: Generates a hash code combining all fields.

## Java-to-C++ Translation Guide

### Data Structure
Implement as a C++ `struct` or `class`.

```cpp
enum class QueryType {
    BY_PACKAGE_NAME = 0,
    BY_UID = 1
};

struct ChangeIdStateQuery {
    QueryType type;
    int64_t changeId;
    std::string packageName; // Use std::optional<std::string> or empty string for null
    int32_t uid;
    int32_t userId;

    // Operator == for map key comparisons
    bool operator==(const ChangeIdStateQuery& other) const {
        return type == other.type &&
               changeId == other.changeId &&
               packageName == other.packageName &&
               uid == other.uid &&
               userId == other.userId;
    }
};
```

### Hashing
To use this as a key in `std::unordered_map`, specialize `std::hash`.

```cpp
namespace std {
    template <>
    struct hash<ChangeIdStateQuery> {
        size_t operator()(const ChangeIdStateQuery& k) const {
            // Combine hashes of all fields
            // Use a standard hash combination helper
            return ...;
        }
    };
}
```

### Memory Management
*   **Java**: Strings are immutable references.
*   **C++**: `std::string` manages its own memory. Copy by value is standard for map keys, but `std::string_view` could be used in lookup interfaces to avoid allocation.

## Test Cases & Validation
1.  **Equality**: `byPackageName(1, "pkg", 0)` must equal another instance created with same params.
2.  **Inequality**: `byPackageName` must not equal `byUid` even if ID matches.
3.  **Hashing**: Equal objects must return same hash code.

## Implementation Risks
*   **String Handling**: Ensure `packageName` null handling in C++ (empty string vs std::nullopt) matches the Java logic (Java uses `null` for UID queries).
*   **Padding**: If using this struct as a raw memory key (not recommended due to std::string), beware of structure padding. Use field-by-field comparison/hashing.
