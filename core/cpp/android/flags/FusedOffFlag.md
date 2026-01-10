# FusedOffFlag - Reverse Engineering Documentation

## Executive Summary
`FusedOffFlag` represents a boolean flag that is statically guaranteed to be `false` at compile time (or at least, immutable runtime false).

## Functionality
- **`getDefault()`**: Always returns `false`.
- **`isEnabled` (in FeatureFlags)**: Always returns `false`.

## Java-to-C++ Translation Guide
- **C++**: `constexpr bool` equivalent, or optimized out by compiler if marked `const`.

## Source Reference
Defined in `FusedOffFlag.java`.
