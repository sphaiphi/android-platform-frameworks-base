# VirtualMouseScrollEvent - Reverse Engineering Documentation

## Executive Summary
`VirtualMouseScrollEvent` represents mouse wheel scrolling.

## Architecture Overview
- **Parcelable**.
- **Immutable**.
- **Builder**.

## Detailed Functionality
- **Data**: `mXAxisMovement`, `mYAxisMovement` (floats, range -1.0 to 1.0).
- **Time**: Nanoseconds.

## Java-to-C++ Translation Guide
- Struct with 2 floats + time.
