# WindowManagerPolicyConstants - Reverse Engineering Documentation

## Executive Summary
`WindowManagerPolicyConstants` defines the constants and flags used for interaction between the `WindowManagerService`, the `PhoneWindowManager` (Policy), and the input system. It includes flags for input dispatching, keyguard transitions, and system UI layers.

## Data Model

### 1. Input Policy Flags
*   **`FLAG_WAKE`**: The event should wake the device.
*   **`FLAG_VIRTUAL`**: The event comes from a software-generated source.
*   **`FLAG_INJECTED`**: The event was injected by an app.
*   **`FLAG_PASS_TO_USER`**: The event is safe to be dispatched to the application.

### 2. Navigation Bar
*   **`NAV_BAR_LEFT/RIGHT/BOTTOM`**: Positioning constants.
*   **`NAV_BAR_MODE_*`**: 3-button, 2-button, or Gestural navigation modes.

### 3. Layer Multipliers
*   **`TYPE_LAYER_MULTIPLIER`**: Defines the Z-order gap between different window types.

## Java-to-C++ Translation Guide
*   **Constants**: Map these directly to C++ `enum` or `constexpr` values. They must match the values expected by the native `InputDispatcher`.

## Implementation Risks
*   **Flag Parity**: Mismatched flags between the policy (Java) and the dispatcher (C++) will lead to broken input behavior (e.g., keys not waking the device).
