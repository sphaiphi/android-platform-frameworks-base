# AppLaunchData - Reverse Engineering Documentation

## Executive Summary
`AppLaunchData` defines data structures for launching applications, supporting launch by Intent category, Role, or specific Component (package/class). It serves as a data carrier for gesture-based app launching mechanisms.

## Architecture Overview
- **Interface**: `AppLaunchData` is the base interface.
- **Implementations**:
  - `CategoryData`: Launches based on an Intent category (e.g., APP_BROWSER).
  - `RoleData`: Launches based on a system role (e.g., ROLE_BROWSER).
  - `ComponentData`: Launches a specific package and class.
- **Factory Methods**: Static methods (`createLaunchDataFor...`) are provided for easy instantiation.

## Detailed Functionality

### AppLaunchData Interface
**Purpose**: Unifies different ways to target an application launch.
**Java-Specific Notes**: Uses `sealed` interface concepts implicitly via inner class implementations, though strictly just a public interface with inner static classes.

### CategoryData
**Purpose**: Targets apps by Intent category.
**Data**: `mCategory` (String).

### RoleData
**Purpose**: Targets apps by RoleManager role name.
**Data**: `mRole` (String).

### ComponentData
**Purpose**: Targets explicit app components.
**Data**: `mPackageName` (String), `mClassName` (String).

## Data Model
All implementations act as immutable value objects (POJOs) with:
- Constructors
- Getters
- `equals()`, `hashCode()`, `toString()` implementations.

## API Reference
- `static AppLaunchData createLaunchDataForCategory(String category)`
- `static AppLaunchData createLaunchDataForRole(String role)`
- `static AppLaunchData createLaunchDataForComponent(String packageName, String className)`
- `static AppLaunchData createLaunchData(String category, String role, String packageName, String className)`: Helper to pick the right type based on non-null inputs.

## Java-to-C++ Translation Guide
- **Interface**: C++ abstract base class or `std::variant` if the set of types is closed and fixed. Given the usage, a `std::variant<CategoryData, RoleData, ComponentData>` might be most idiomatic in modern C++.
- **String**: Use `std::string`.
- **Nullability**: Java `null` checks translate to `std::optional` or checks before variant construction.

## Test Cases & Validation
- Verify `createLaunchData` prioritizes Category > Role > Component if multiple are provided (logic is sequential if-checks).
- Verify equality and hash code correctness for identical data.

## Implementation Risks
- None significantly. Pure data containers.
