# Instance - Reverse Engineering Documentation

## Executive Summary
`Instance` represents a normalized gesture sample prepared for classification. It acts as a feature vector.

## Architecture Overview
- **Data**: `float[] vector` (features), `String label`, `long id`.

## Detailed Functionality
- **Normalization**: Normalizes the vector magnitude to 1.
- **Factory (`createInstance`)**:
  - **Temporal**: Resamples the stroke, centers it, rotates it to a canonical orientation, and uses the point coordinates as features.
  - **Spatial**: Rasterizes the gesture into a bitmap patch and uses pixel values as features.

## Java-to-C++ Translation Guide
- **Vector Math**: Operations like normalization and rotation.

## Source Reference
Defined in `Instance.java`.
