# DisplayTopologyGraph - Reverse Engineering Documentation

## Executive Summary
`DisplayTopologyGraph` is a graph representation derived from `DisplayTopology`. While the topology is a tree (for layout definition), the graph represents adjacencies (useful for navigation, cursor movement across screens).

## Data Model
- **Records** (Java 16+ feature): `DisplayNode`, `AdjacentDisplay`.
- `DisplayNode`: `displayId`, `density`, `AdjacentDisplay[]`.
- `AdjacentDisplay`: `displayId`, `position` (where the neighbor is), `offsetDp`.

## Java-to-C++ Translation Guide
- Simple struct/class mapping.
- **Records**: Map to `struct` with all public members.
