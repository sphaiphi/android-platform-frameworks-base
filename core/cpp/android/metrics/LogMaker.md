# LogMaker - Reverse Engineering Documentation

## Executive Summary
`LogMaker` is a builder pattern implementation designed to assemble structured metric events for the Android platform. It acts as an intermediate data holder that collects various properties (categories, types, timestamps, and custom tagged data) before they are serialized and written to the system's `EventLog`. It serves as the primary interface for constructing complex log entries that satisfy the Android Metrics protocol.

## Architecture Overview
- **Pattern**: Builder Pattern (Fluent API).
- **Core Component**: Wraps a dynamic collection of key-value pairs representing log attributes.
- **Dependencies**:
    - `android.util.SparseArray`: Used for efficient storage of integer-keyed properties.
    - `com.android.internal.logging.nano.MetricsProto.MetricsEvent`: Source of truth for property keys (categories, types, etc.).
    - `android.util.Log` / `android.content.ComponentName`: Utilities for logging and component identification.

## Detailed Functionality

### Core Data Storage
The class relies on a single `SparseArray<Object>` named `entries` to store all log properties.
- **Keys**: Integers defined in `MetricsEvent` (e.g., `RESERVED_FOR_LOGBUILDER_CATEGORY`).
- **Values**: Can be `Integer`, `Long`, `Float`, or `String`.

### serialization/Deserialization
**Purpose**: To convert the structured `LogMaker` object into a flat array format suitable for the low-level `EventLog` API, and vice-versa.
- **Serialization (`serialize()`)**:
    - Flattens the `entries` map into an `Object[]`.
    - Format: `[key1, value1, key2, value2, ...]`.
    - **Constraint**: The serialized byte size must not exceed `MAX_SERIALIZED_SIZE` (4000 bytes).
- **Deserialization (`deserialize(Object[])`)**:
    - Reconstructs the `entries` map from a flat array.
    - Validates that keys are Integers.

### Fluent Setters
Methods like `setCategory`, `setType`, `setPackageName` return `this` to allow method chaining. They map specific semantic properties to reserved integer keys in the `entries` array.

## Data Model

### `entries` (SparseArray<Object>)
Primary state container.
- **Invariants**:
    - Keys are generally constants from `MetricsProto.MetricsEvent`.
    - Values are strictly typed to `Integer`, `Long`, `Float`, or `String` (enforced by `isValidValue`).

### Reserved Keys
Mapping of semantic properties to `MetricsEvent` constants:
| Property | Type | Key Constant |
| :--- | :--- | :--- |
| Category | `int` | `RESERVED_FOR_LOGBUILDER_CATEGORY` |
| Type | `int` | `RESERVED_FOR_LOGBUILDER_TYPE` |
| Subtype | `int` | `RESERVED_FOR_LOGBUILDER_SUBTYPE` |
| Latency | `long` | `RESERVED_FOR_LOGBUILDER_LATENCY_MILLIS` |
| Timestamp | `long` | `RESERVED_FOR_LOGBUILDER_TIMESTAMP` |
| Package Name | `String` | `RESERVED_FOR_LOGBUILDER_PACKAGENAME` |
| Process ID | `int` | `RESERVED_FOR_LOGBUILDER_PID` |
| UID | `int` | `RESERVED_FOR_LOGBUILDER_UID` |
| Counter Name | `String` | `RESERVED_FOR_LOGBUILDER_NAME` |
| Counter Bucket | `int`/`long`| `RESERVED_FOR_LOGBUILDER_BUCKET` |
| Counter Value | `int` | `RESERVED_FOR_LOGBUILDER_VALUE` |

## API Reference

### Constructors
- `LogMaker(int category)`: Initializes with a specific category.
- `LogMaker(Object[] items)`: Reconstructs object from a serialized array.

### Public Methods
- **Setters (`set*`)**: Set specific fields (Category, Type, Subtype, Latency, Timestamp, PackageName, Pid, Uid, Counter info). All return `LogMaker`.
- **Getters (`get*`)**: Retrieve fields with type safety checks. Return default values (0, -1, null) if the field is missing or wrong type.
- **`addTaggedData(int tag, Object value)`**: Adds generic key-value pair. Validates value type.
- **`serialize()`**: Returns `Object[]`. Throws `RuntimeException` if size exceeds limit.
- **`isSubsetOf(LogMaker that)`**: Checks if all keys/values in `this` exist and match in `that`.

## Java-to-C++ Translation Guide

### Data Structures
- **`SparseArray<Object>`**:
    - **C++ Replacement**: `std::map<int, std::variant<int, int64_t, float, std::string>>` or a `std::vector<std::pair<int, Variant>>` (sorted for fast lookup if needed).
    - **Note**: `SparseArray` is an optimization for int keys. In C++, a flat map is often comparable.

### Dynamic Types
- **Java**: `Object` (runtime checked via `instanceof`).
- **C++**: Use `std::variant` to enforce the allowed types (`int`, `long`, `float`, `String`).

### Serialization
- **Java**: Returns `Object[]` (array of pointers).
- **C++**: Should likely return a structured buffer or a `std::vector<EventLog::TagValue>` depending on the C++ `EventLog` API equivalent. The "flat array" concept might need to be adapted to the specific IPC or logging mechanism used in the native layer (e.g., AStatsSocket).

### Memory Management
- **Java**: Garbage collected.
- **C++**: The `LogMaker` should own its data (strings). Copy semantics should be defined (likely deep copy).

## Test Cases & Validation

### Usage Example
```cpp
// C++ Pseudo-code
LogMaker builder(MetricsEvent::VIEW_MAIN);
builder.setPackageName("com.android.settings")
       .addTaggedData(123, 456);

// Serialization check
auto serialized = builder.serialize();
// Expected: [CATEGORY_KEY, VIEW_MAIN, PACKAGENAME_KEY, "com.android.settings", 123, 456]
```

### Edge Cases
1.  **Serialization Limit**: Adding data that causes `serialize()` to exceed 4000 bytes should trigger a warning or error.
2.  **Type Mismatches**: `addTaggedData` must reject types other than int, long, float, string.
3.  **Null Values**: `addTaggedData` with `null` should act as `clearTaggedData`.

## Implementation Risks
- **Endianness/Size**: Ensure `long` in Java (64-bit) maps correctly to `int64_t` in C++. Java `int` is 32-bit.
- **String Encoding**: Java Strings are UTF-16. C++ implementation typically uses UTF-8. Ensure conversion happens during serialization if the underlying transport expects bytes.
