# VirtualDpad - Reverse Engineering Documentation

## Executive Summary
`VirtualDpad` allows injecting D-pad events (Up, Down, Left, Right, Center, Back) from a virtual device into the system.

## Architecture Overview
- **Inheritance**: Extends `VirtualInputDevice`.
- **Validation**: Enforces allowed key codes.

## Detailed Functionality
- **Constructor**: Registers device via `VirtualInputDevice` mechanism.
- **sendKeyEvent**: Validates the keycode against `mSupportedKeyCodes`. Calls `mVirtualDevice.sendDpadKeyEvent`.

## Allowed Keys
- DPAD_UP, DPAD_DOWN, DPAD_LEFT, DPAD_RIGHT, DPAD_CENTER, BACK.

## Java-to-C++ Translation Guide
- **Logic**: Validation logic + IPC call.

## Test Cases & Validation
- Send allowed key -> Success.
- Send disallowed key (e.g., 'A') -> Throws IllegalArgumentException.
