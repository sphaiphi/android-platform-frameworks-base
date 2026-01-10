# GestureUtils - Reverse Engineering Documentation

## Executive Summary
`GestureUtils` provides static utility functions for geometric processing, sampling, and comparison of gestures.

## Detailed Functionality

### Sampling
- **`spatialSampling`**: Renders the gesture into a fixed-size grid (bitmap), useful for image-based recognition. Handles aspect ratio scaling.
- **`temporalSampling`**: Resamples a stroke into a fixed number of equidistant points.

### Geometry
- `computeCentroid`: Finds the center of mass.
- `computeCoVariance`: Computes the covariance matrix (for orientation).
- `computeOrientedBoundingBox`: Finds the minimum bounding box rotated to align with the gesture's principal axis.
- `rotate`, `translate`, `scale`: Affine transformations on point arrays.

### Distances
- `squaredEuclideanDistance`: Standard L2 distance.
- `cosineDistance`: Angle between vectors.
- `minimumCosineDistance`: Cosine distance optimized over possible orientations (rotations).

## Java-to-C++ Translation Guide
- **Math**: Heavily relies on linear algebra. C++ libraries like Eigen could optimize this, or standard `cmath` implementation.
- **Algorithms**: The sampling and plotting algorithms (Bresenham-like) are logic-heavy and should be ported carefully.

## Source Reference
Defined in `GestureUtils.java`.
