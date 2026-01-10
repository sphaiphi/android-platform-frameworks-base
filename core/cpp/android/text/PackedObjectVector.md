# PackedObjectVector - Reverse Engineering Documentation

## Executive Summary
Similar to `PackedIntVector` but for Objects. Used by `DynamicLayout` to store objects per line (e.g. `Directions`).

## Data Model
- Gap buffer for rows.

## Java-to-C++ Translation Guide
- Template class `PackedVector<T>`.
