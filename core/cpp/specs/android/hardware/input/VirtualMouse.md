# VirtualMouse - Reverse Engineering Documentation

## Executive Summary
`VirtualMouse` allows injecting mouse events: relative movement, buttons, scrolling, and retrieving cursor position.

## Architecture Overview
- **Inheritance**: Extends `VirtualInputDevice`.

## Detailed Functionality
- **sendButtonEvent**: Clicks (Left, Right, Middle, etc.).
- **sendScrollEvent**: Wheel scrolling (X/Y).
- **sendRelativeEvent**: Mouse movement (dX, dY).
- **getCursorPosition**: Synchronous IPC to fetch current pointer location.

## Java-to-C++ Translation Guide
- Proxy methods to IPC.

## Implementation Risks
- `getCursorPosition` is blocking and might be slow.
