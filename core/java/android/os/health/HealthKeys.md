# HealthKeys - Reverse Engineering Documentation

## Executive Summary
`HealthKeys` acts as a central registry and metadata manager for the health statistics subsystem (`android.os.health`). It defines the types of metrics available (Timers, Measurements, Stats, etc.) and provides a mechanism (`Constants` inner class) to introspect other classes (like `UidHealthStats`, `PidHealthStats`) to dynamically build mappings of integer keys to their storage indices. This infrastructure allows for efficient, array-based storage of diverse health metrics.

## Architecture Overview
-   **Role**: Metadata definition and Key Registry.
-   **Core Concepts**:
    -   **Metric Types**: 5 fundamental types (`TIMER`, `MEASUREMENT`, `STATS`, `TIMERS`, `MEASUREMENTS`).
    -   **Key Segmentation**: Keys are segmented by base offsets (e.g., `BASE_UID = 10000`, `BASE_PID = 20000`) for readability/debugging, though functionally they are just unique identifiers.
    -   **Introspection**: Uses Java Reflection to scan classes for `@Constant` annotations to build key lookup tables.

## Detailed Functionality

### Metric Types
-   `TYPE_TIMER` (0): Count + Duration.
-   `TYPE_MEASUREMENT` (1): Single `long` value (count, time, etc.).
-   `TYPE_STATS` (2): Recursive `HealthStats` map.
-   `TYPE_TIMERS` (3): Map of String -> `TimerStat`.
-   `TYPE_MEASUREMENTS` (4): Map of String -> `Long`.

### `HealthKeys.Constants` (Inner Class)
This class performs the heavy lifting of key management.
-   **Input**: A class (e.g., `UidHealthStats.class`).
-   **Mechanism**:
    1.  Reflects over all fields of the input class.
    2.  Filters for `@Constant` annotation.
    3.  Reads the static int value of the field (the "key").
    4.  Sorts these keys into arrays based on their `type`.
-   **Output**: Lookup tables (`mKeys` array of arrays) allowing O(log N) lookup of a key's index within its type category via `binarySearch`.

### `SortedIntArray` (Inner Class)
-   Simple helper to build a sorted `int[]` for binary search efficiency.

## Data Model
-   **Constant Types**: Integer constants representing metric categories.
-   **Key Structure**:
    -   `BASE_UID` (10000)
    -   `BASE_PID` (20000)
    -   `BASE_PROCESS` (30000)
    -   `BASE_PACKAGE` (40000)
    -   `BASE_SERVICE` (50000)

## API Reference
-   `Constants(Class clazz)`: Constructor that builds the index.
-   `Constants.getIndex(int type, int key)`: Returns the array index for a given global key. Throws runtime exception if not found.
-   `Constants.getKeys(int type)`: Returns all known keys for a specific type.
-   `Constants.getSize(int type)`: Returns count of metrics for a type.

## Java-to-C++ Translation Guide

### Architecture
-   This class relies heavily on **Java Reflection** to build indices at runtime. C++ does not support reflection in the same way.
-   **Translation Strategy**:
    -   **Code Generation**: The most robust C++ equivalent is to use a code generator (python script or similar) that parses the constant definitions and generates C++ arrays/maps at compile time.
    -   **Manual Mapping**: If code gen is overkill, manually maintain `std::map<int, int>` or sorted `std::vector`s for key-to-index mapping.
    -   **X-Macro**: Use C Preprocessor X-Macros to define keys and automatically generate both the enum/const definitions and the lookup arrays.

### Key Mapping
| Java Feature | C++ Equivalent | Notes |
| :--- | :--- | :--- |
| `annotation @Constant` | N/A (or custom attribute) | Use a naming convention or external IDL/definition file. |
| `int[][] mKeys` | `std::vector<std::vector<int>>` | Or flat arrays if sizes are fixed at compile time. |
| `Arrays.binarySearch` | `std::lower_bound` | Standard algorithm for sorted lookup. |

## Questions for C++ Team
1.  Are these keys defined in an AIDL file? If so, the AIDL compiler might already generate C++ constants.
2.  Do we need the dynamic lookup capability, or can we hardcode the indices if the C++ side is the producer (HealthStatsWriter)?