# KeyGestureEvent - Reverse Engineering Documentation

## Executive Summary
`KeyGestureEvent` represents a high-level keyboard gesture (e.g., "Home", "Back", "Brightness Up") triggered by an external keyboard. It wraps `AidlKeyGestureEvent`.

## Architecture Overview
- **Wrapper**: Encapsulates `AidlKeyGestureEvent`.
- **Constants**: Defines a large set of `KEY_GESTURE_TYPE_*` constants.
- **Builder**: For creation (mostly testing).

## Detailed Functionality

### Data Access
- **Device**: `getDeviceId()`.
- **Keycodes**: Raw keys involved (`int[]`).
- **Modifiers**: State of Shift, Ctrl, etc.
- **Gesture Type**: The semantic meaning (e.g., `KEY_GESTURE_TYPE_HOME`).
- **Action**: `ACTION_GESTURE_START` / `COMPLETE` / `CANCEL`.

### Logging
- **getLogEvent()**: Maps internal gesture types to `FrameworkStatsLog` atoms for telemetry.

## Data Model
- `AidlKeyGestureEvent mKeyGestureEvent`.

## API Reference
- `getKeyGestureType()`
- `getAction()`
- `hasModifiers(int modifiers)`

## Java-to-C++ Translation Guide
- **Enum**: `KeyGestureType` constants map to a C++ enum.
- **StatsLog**: C++ needs to map these to the native StatsLog API.

## Implementation Risks
- Maintaining consistency of `KEY_GESTURE_TYPE` constants if they are persisted or shared across boundaries.
