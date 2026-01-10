# OneTimeUseBuilder - Reverse Engineering Documentation

## Executive Summary
`OneTimeUseBuilder` is a utility base class for Builders that enforce a single-use contract (throwing exception if reused).

## Architecture Overview
- **Type**: Abstract Base Class.
- **Generics**: `T` (Type being built).

## Detailed Functionality
-   `markUsed()` sets a flag.
-   `checkNotUsed()` throws if flag is set.

## Java-to-C++ Translation Guide
-   **Pattern**: Can be implemented as a mixin or base class in C++.
