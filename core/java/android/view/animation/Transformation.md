# Transformation - Reverse Engineering Documentation

## Executive Summary
Defines the transformation to be applied at a point in time. It holds a Matrix and an Alpha value.

## Data Model
*   `mMatrix`: 3x3 Matrix.
*   `mAlpha`: Float opacity (0.0 - 1.0).
*   `mTransformationType`: Optimization flag (Identity, Alpha, Matrix, Both).
*   `mClipRect`: Optional clipping bounds.

## Key Algorithms
*   **`compose`**: Combines two transformations (matrix multiplication, alpha multiplication).

## Java-to-C++ Translation Guide
*   **Matrix**: Core component.
