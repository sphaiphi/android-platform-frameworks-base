# VirtualKeyboard - Reverse Engineering Documentation

## Executive Summary
`VirtualKeyboard` allows injecting full keyboard events into the system.

## Architecture Overview
- **Inheritance**: Extends `VirtualInputDevice`.

## Detailed Functionality
- **sendKeyEvent**: Injects `VirtualKeyEvent`.
- **Restrictions**: Explicitly rejects `KEYCODE_DPAD_CENTER` (likely legacy reason or conflict with Dpad).

## Java-to-C++ Translation Guide
- Wrapper around IPC call.

## Test Cases
- Send 'A' key -> Success.
- Send DPAD_CENTER -> Exception.
