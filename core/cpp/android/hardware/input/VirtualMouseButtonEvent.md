# VirtualMouseButtonEvent - Reverse Engineering Documentation

## Executive Summary
`VirtualMouseButtonEvent` represents a mouse button press or release.

## Architecture Overview
- **Parcelable**.
- **Immutable**.
- **Builder**.

## Detailed Functionality
- **Data**: Action (Press/Release), Button Code (Primary, Secondary, Tertiary, Back, Forward).
- **Time**: Nanoseconds.

## Java-to-C++ Translation Guide
- Struct.
