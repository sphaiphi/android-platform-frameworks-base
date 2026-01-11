# DisplayTopology - Reverse Engineering Documentation

## Executive Summary
`DisplayTopology` represents the physical layout of connected displays relative to each other (e.g., "Display B is to the right of Display A"). It uses a tree structure where one display is the root, and others are attached to edges of their parents.

## Architecture Overview
- **Type**: Parcelable Data Structure.
- **Structure**: Tree (`TreeNode`).
- **Coordinate System**: Density-independent pixels (dp) or logic pixels? *Code says density-independent pixels (dp) for offsets/sizes in TreeNode.*

## Detailed Functionality

### TreeNode
- `displayId`
- `width`, `height` (in dp)
- `position`: LEFT, TOP, RIGHT, BOTTOM (relative to parent).
- `offset`: Distance along the edge (in dp).

### Logic
- **Normalization**: `normalize()` clamps offsets and resolves overlaps to ensure a valid non-overlapping layout.
- **Rearrange**: `rearrange(Map<Integer, PointF>)` attempts to automatically generate a tree structure that best fits a set of arbitrary 2D positions (e.g., from a UI drag-and-drop interface). It uses a greedy algorithm to attach "islands" of displays.
- **Flattening**: `getAbsoluteBounds()` calculates the absolute 2D RectF for every display starting from the root at (0,0).

## Java-to-C++ Translation Guide
- **Recursive Logic**: The tree traversal (get info, clamping) is recursive. C++ implementation should be careful of stack depth or use iterative approaches.
- **Math**: Extensive use of `RectF` and float math.
- **Algorithms**: The `rearrange` logic is non-trivial heuristic optimization. It needs to be ported carefully to match behavior.

## API Reference
- `addDisplay(id, w, h)`
- `removeDisplay(id)`
- `getGraph()`: Returns a graph representation for adjacency.
