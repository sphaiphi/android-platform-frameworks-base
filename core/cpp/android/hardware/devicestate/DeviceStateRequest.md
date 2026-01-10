# DeviceStateRequest - Reverse Engineering Documentation

## Executive Summary
`DeviceStateRequest` encapsulates the parameters required to request a device state change. It uses a Builder pattern to construct requests with a specific target state identifier and optional flags.

## Architecture Overview
- **Type**: Immutable Data Object
- **Package**: `android.hardware.devicestate`

## Detailed Functionality

### Properties
- **Requested State**: `int` (The target state identifier).
- **Flags**: `int` (Bitmask).
    - `FLAG_CANCEL_WHEN_BASE_CHANGES` (1 << 0): Automatically cancel this request if the physical device state changes.

### Builder Pattern
- `newBuilder(int requestedState)`: Static entry point.
- `setFlags(int flags)`: Accumulates flags.
- `build()`: Creates the instance.

## Java-to-C++ Translation Guide

### Type Mapping
- `DeviceStateRequest` -> `struct` or `class` in C++.
- Flags should be an `enum` or `bitfield`.

### Logic
- Simple data holder. No complex logic.
- Ensure the flags match the Java definitions exactly.

## API Reference
- `getState()`: Returns `int`.
- `getFlags()`: Returns `int`.
