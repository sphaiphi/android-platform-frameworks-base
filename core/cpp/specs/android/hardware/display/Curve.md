# Curve - Reverse Engineering Documentation

## Executive Summary
`Curve` is a simple Parcelable wrapper for two float arrays (`x` and `y`) representing a mathematical curve. It is primarily used to transport the "Minimum Brightness Curve" from system server to clients.

## Data Model
- `float[] mX`: Domain points.
- `float[] mY`: Range points.

## Java-to-C++ Translation Guide
- Simple `struct` with two vectors.
- Parceling: Write X array, then Y array.
