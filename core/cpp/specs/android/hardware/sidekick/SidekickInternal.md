# SidekickInternal.java - Reverse Engineering Documentation

## Executive Summary
`SidekickInternal` defines an internal local system service interface for interacting with "Sidekick" hardware. This likely refers to a co-processor or a dedicated low-power display controller (common in wearables like Wear OS devices) that manages the screen when the main application processor (AP) is suspended or in a low-power state.

## Architecture Overview
- **Type**: Abstract Base Class (Local Service Interface)
- **Package**: `android.hardware.sidekick`
- **Visibility**: `@hide` (Internal System API)
- **Target Audience**: System Server, Clockwork Home (Wear OS Launcher).

## Detailed Functionality

### Core Responsibilities
The interface provides methods to coordinate display ownership between the main Android system and the Sidekick hardware.

1.  **Reset**: Resets the Sidekick hardware to a clean state (powered-on default).
2.  **Start Control**: Grants the Sidekick hardware permission/instruction to take over display updates (e.g., for Always-On Display or low-power watch faces).
3.  **End Control**: Revokes display control from Sidekick, returning it to the main Android system.

### Display States
The `startDisplayControl` method accepts a `displayState` integer. Based on the documentation, expected values correspond to constants in `android.view.Display`, specifically:
- `Display.STATE_DOZE_SUSPEND`
- `Display.STATE_ON_SUSPEND`

This confirms the usage in power transition scenarios (Doze/Suspend).

## API Reference

### Methods

| Method | Return Type | Arguments | Description |
| :--- | :--- | :--- | :--- |
| `reset()` | `boolean` | None | Resets Sidekick. Returns `true` if successful. Guarantees Sidekick is *not* controlling display upon return. |
| `startDisplayControl(int displayState)` | `boolean` | `int displayState` | Signals Sidekick to take control. Returns `true` on success. |
| `endDisplayControl()` | `void` | None | Signals Sidekick to stop controlling display. Must always succeed. |

## Java-to-C++ Translation Guide

### C++ Interface Suggestion
Since this is an internal system service interface, the implementation typically lives in a native service or a Java service with JNI calls. A C++ translation would define an abstract interface (pure virtual class).

```cpp
namespace android {
namespace hardware {
namespace sidekick {

class ISidekickInternal {
public:
    virtual ~ISidekickInternal() = default;

    /**
     * Resets Sidekick to power-on state.
     * @return true on success.
     */
    virtual bool reset() = 0;

    /**
     * Starts display control.
     * @param displayState Corresponds to Display.STATE_* constants.
     * @return true on success.
     */
    virtual bool startDisplayControl(int displayState) = 0;

    /**
     * Ends display control.
     */
    virtual void endDisplayControl() = 0;
};

} // namespace sidekick
} // namespace hardware
} // namespace android
```

### Key Considerations
- **Concurrency**: The Java doc implies strictly synchronous behavior ("upon return Sidekick is guaranteed..."). The C++ implementation must ensure hardware operations block until completion or strictly guarantee state before returning.
- **Error Handling**: `reset` and `startDisplayControl` return booleans indicating availability. `endDisplayControl` is void and assumes success.

## Usage Context
This interface is likely retrieved via `LocalServices.getService(SidekickInternal.class)` within the System Server process (e.g., inside `PowerManagerService` or `DisplayPowerController`).
