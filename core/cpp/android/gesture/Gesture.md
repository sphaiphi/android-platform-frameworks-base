# Gesture - Reverse Engineering Documentation

## Executive Summary
`Gesture` represents a hand-drawn shape on a touch screen. It is a container for one or more `GestureStroke`s and provides methods for serializing, deserializing, rendering (to Path or Bitmap), and analyzing (length, bounding box) the gesture. It implements `Parcelable` for inter-process communication.

## Architecture Overview
- **Data Structure**: Composed of a list of `GestureStroke` objects (`ArrayList<GestureStroke>`).
- **Identification**: Each gesture has a unique ID (`mGestureID`) generated from a base time and an atomic counter.
- **Serialization**: Supports both custom binary serialization (`DataOutputStream`) and Android `Parcelable`.

## Detailed Functionality

### Core Data
- `mStrokes`: List of strokes forming the gesture.
- `mBoundingBox`: The union of all stroke bounding boxes.
- `mGestureID`: Unique identifier.

### Rendering
- `toPath()`: Converts all strokes into a single `android.graphics.Path`.
- `toBitmap()`: Renders the gesture into a `Bitmap` with configurable stroke width, color, and optional scaling/insetting.

### Metrics
- `getLength()`: Sum of lengths of all strokes.
- `getBoundingBox()`: Returns the pre-calculated bounding box.

### Serialization
- **Binary Format**:
  - Gesture ID (long)
  - Stroke Count (int)
  - [Stroke Data...] (Recursively calls `GestureStroke.serialize`)

## Data Model
- **Strokes**: Ordered sequence of user inputs.
- **Bounding Box**: `RectF` covering the extent of the gesture.

## Java-to-C++ Translation Guide
- **Graphics**: `android.graphics.Path` and `Bitmap` need C++ equivalents (e.g., Skia `SkPath`, `SkBitmap` if available, or a custom geometry class).
- **AtomicInteger**: Use `std::atomic<int>`.
- **Serialization**: The binary format is simple (Big Endian by default in Java `DataOutputStream`). C++ implementation must ensure correct endianness.

## Source Reference
Defined in `Gesture.java`.
