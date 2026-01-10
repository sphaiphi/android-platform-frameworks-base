# Flag - Reverse Engineering Documentation

## Executive Summary
`Flag` is the generic interface for all feature flags.

## API Reference
- **`getNamespace()`**: String.
- **`getName()`**: String.
- **`getDefault()`**: T.
- **`isDynamic()`**: boolean.
- **`defineMetaData(...)`**: fluent builder for labels/descriptions.

## Java-to-C++ Translation Guide
- **C++**: `template <typename T> class Flag`.

## Source Reference
Defined in `Flag.java`.
