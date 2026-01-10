# FeatureFlagsFake - Reverse Engineering Documentation

## Executive Summary
`FeatureFlagsFake` is a testing utility that extends `FeatureFlags`, allowing tests to manually set flag values and ensuring hermetic execution.

## Architecture Overview
- **Usage**: Used in Unit Tests via dependency injection or `FeatureFlags.setInstance()`.

## Detailed Functionality
- **`setFlagValue`**: Manually sets the return value for a specific flag object.
- **`requireFlag`**: Enforces that tests explicitly set values for flags they read (fail-fast).
- **`syncInternal`**: No-op (mocks out IPC).

## Java-to-C++ Translation Guide
- **C++**: Mock class inheriting from the C++ `FeatureFlags` class.

## Source Reference
Defined in `FeatureFlagsFake.java`.
