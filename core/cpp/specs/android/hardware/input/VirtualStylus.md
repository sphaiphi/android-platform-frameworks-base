# VirtualStylus - Reverse Engineering Documentation

## Executive Summary
`VirtualStylus` allows injecting stylus (pen) events, including pressure, tilt, and button presses.

## Architecture Overview
- **Inheritance**: Extends `VirtualInputDevice`.

## Detailed Functionality
- **sendMotionEvent**: Injects `VirtualStylusMotionEvent` (Coordinates, Pressure, Tilt).
- **sendButtonEvent**: Injects `VirtualStylusButtonEvent` (Primary/Secondary buttons).

## Java-to-C++ Translation Guide
- Wrapper for IPC.
