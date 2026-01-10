# GesturePoint - Reverse Engineering Documentation

## Executive Summary
`GesturePoint` represents a single coordinate in a gesture stroke, including a timestamp.

## Data Model
- `float x, y`: Spatial coordinates.
- `long timestamp`: Time of the point event.

## Java-to-C++ Translation Guide
- **C++**: Simple struct/class `struct GesturePoint { float x, y; int64_t timestamp; };`.

## Source Reference
Defined in `GesturePoint.java`.
