# VirtualStylusMotionEvent - Reverse Engineering Documentation

## Executive Summary
`VirtualStylusMotionEvent` represents the movement and state of a stylus (coordinates, pressure, tilt).

## Architecture Overview
- **Parcelable**.
- **Immutable**.
- **Builder**.

## Detailed Functionality
- **Data**:
  - `mToolType`: Stylus or Eraser.
  - `mAction`: Down, Up, Move.
  - `mX`, `mY`: Integer coordinates.
  - `mPressure`: Int (0-255).
  - `mTiltX`, `mTiltY`: Int degrees (-90 to 90).
- **Validation**: Range checks on pressure and tilt.

## Java-to-C++ Translation Guide
- Struct with integers. Note that coordinates are `int` here, unlike mouse/touch which often use `float`.

## Implementation Risks
- Coordinate space matching the display dimensions.
