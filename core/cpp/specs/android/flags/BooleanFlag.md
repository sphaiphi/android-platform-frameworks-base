# BooleanFlag - Reverse Engineering Documentation

## Executive Summary
`BooleanFlag` represents a boolean feature flag whose value remains constant throughout the process lifetime.

## Architecture Overview
- **Inheritance**: Extends `BooleanFlagBase`, which implements `Flag<Boolean>`.
- **Immutability**: Designed to be read-only after initialization.

## Detailed Functionality
- **Constructor**: Takes namespace, name, and default value.
- **`getDefault()`**: Returns the fixed default value.
- **`defineMetaData`**: Fluent API for adding label, description, and category.

## Data Model
- `boolean mDefault`: The hardcoded default value.

## Java-to-C++ Translation Guide
- **C++**: Can be mapped to a `const bool` or a simple struct with a getter.
- **Usage**: Used for stable feature flags that don't need runtime updates.

## Source Reference
Defined in `BooleanFlag.java`.
