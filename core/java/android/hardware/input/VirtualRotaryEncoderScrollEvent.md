# VirtualRotaryEncoderScrollEvent - Reverse Engineering Documentation

## Executive Summary
`VirtualRotaryEncoderScrollEvent` represents a rotation event.

## Architecture Overview
- **Parcelable**.
- **Immutable**.
- **Builder**.

## Detailed Functionality
- **Data**: `mScrollAmount` (float, -1.0 to 1.0).
- **Time**: Nanoseconds.

## Java-to-C++ Translation Guide
- Struct with 1 float + time.
