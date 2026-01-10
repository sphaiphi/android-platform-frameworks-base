# GestureStroke - Reverse Engineering Documentation

## Executive Summary
`GestureStroke` represents a continuous stroke (Touch Down to Touch Up). It calculates its own bounding box, length, and cached Path.

## Architecture Overview
- **Data**: Raw points array (`float[]`), timestamps (`long[]`), and bounding box (`RectF`).
- **Path Generation**: lazily computes `mCachedPath` using quadratic Bezier curves for smoothing.

## Detailed Functionality
- **Constructor**: Analyzing input points to compute total length and bounding box.
- **Sampling**: `toPath(width, height, numSample)` performs temporal sampling to generate a normalized path.
- **Serialization**: Writes raw point data to `DataOutputStream`.

## Java-to-C++ Translation Guide
- **Math**: Uses `Math.hypot`.
- **Path**: Path construction logic (`quadTo`) is critical for visual consistency.

## Source Reference
Defined in `GestureStroke.java`.
