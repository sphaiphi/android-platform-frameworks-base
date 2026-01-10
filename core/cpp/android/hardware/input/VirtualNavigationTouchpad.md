# VirtualNavigationTouchpad - Reverse Engineering Documentation

## Executive Summary
`VirtualNavigationTouchpad` represents a touchpad used for navigation (like a D-pad via gestures) rather than a pointer.

## Architecture Overview
- **Inheritance**: Extends `VirtualInputDevice`.

## Detailed Functionality
- **sendTouchEvent**: Injects `VirtualTouchEvent`.
- **Note**: Acts as `SOURCE_TOUCH_NAVIGATION`.

## Java-to-C++ Translation Guide
- Wrapper for IPC.
