# ComponentCallbacks2 - Reverse Engineering Documentation

## Executive Summary
`ComponentCallbacks2` extends `ComponentCallbacks` to provide finer-grained memory management callbacks (`onTrimMemory`).

## Architecture Overview
- **Inheritance:** Extends `ComponentCallbacks`.

## Detailed Functionality
- **`onTrimMemory(int level)`**: Provides a hint (integer level) indicating the severity of memory pressure.

## Constants (Trim Levels)
- `TRIM_MEMORY_COMPLETE` (80)
- `TRIM_MEMORY_MODERATE` (60)
- `TRIM_MEMORY_BACKGROUND` (40)
- `TRIM_MEMORY_UI_HIDDEN` (20)
- `TRIM_MEMORY_RUNNING_CRITICAL` (15)
- `TRIM_MEMORY_RUNNING_LOW` (10)
- `TRIM_MEMORY_RUNNING_MODERATE` (5)

## API Reference
- `void onTrimMemory(int level)`

## Java-to-C++ Translation Guide
- Pure virtual abstract class in C++.
- Constants should be mapped to an enum or `static const int`.

## Implementation Risks
- **Interpretation**: Implementations must handle any integer value, not just the constants, as intermediate levels are possible.
