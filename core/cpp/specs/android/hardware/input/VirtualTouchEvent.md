# VirtualTouchEvent - Reverse Engineering Documentation

## Executive Summary
`VirtualTouchEvent` represents a single touch pointer event (finger or palm).

## Architecture Overview
- **Parcelable**.
- **Immutable**.
- **Builder**.

## Detailed Functionality
- **Data**:
  - `mPointerId`: 0-15.
  - `mToolType`: Finger or Palm.
  - `mAction`: Down, Up, Move, Cancel.
  - `mX`, `mY`: Float coordinates.
  - `mPressure`: Float.
  - `mMajorAxisSize`: Float (contact area).
- **Validation**: Pointer ID range, required fields, Cancel/Palm pairing.

## Java-to-C++ Translation Guide
- Struct. Note float coordinates.

## Implementation Risks
- Multi-touch handling: The system expects a stream of these events for each pointer.
