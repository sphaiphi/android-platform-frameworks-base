# VirtualMouseRelativeEvent - Reverse Engineering Documentation

## Executive Summary
`VirtualMouseRelativeEvent` represents relative mouse movement (deltas).

## Architecture Overview
- **Parcelable**.
- **Immutable**.
- **Builder**.

## Detailed Functionality
- **Data**: `mRelativeX`, `mRelativeY` (floats).
- **Time**: Nanoseconds.

## Java-to-C++ Translation Guide
- Struct with 2 floats + time.
