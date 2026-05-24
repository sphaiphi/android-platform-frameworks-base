# TrustAgentService - Reverse Engineering Documentation

## Executive Summary
`TrustAgentService` is a system service base class used to implement "Smart Lock" features. It allows trusted applications (typically platform-provided) to notify the system when the device's environment is considered secure (e.g., near a trusted Bluetooth device or at a trusted location), thereby bypassing the requirement for a PIN, pattern, or password to unlock the keyguard.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC**: Implements `ITrustAgentService.Stub`. It receives a `ITrustAgentServiceCallback` from the system to report trust events.
*   **Lifecycle**: The system binds to the agent when the device is locked or when trust management is needed.
*   **Permission**: Requires `android.permission.BIND_TRUST_AGENT`.
*   **Threading**: Binder calls are marshalled to a local `Handler` thread to ensure serialized execution of lifecycle methods.

## Detailed Functionality

### Trust Management
*   **`setManagingTrust(boolean)`**: Informs the system that the agent is currently active and evaluating trust conditions.
*   **`grantTrust(message, durationMs, flags)`**: Notifies the system that the device is trusted. The system will keep the device unlocked for `durationMs` or until revoked.
    *   `FLAG_GRANT_TRUST_DISMISS_KEYGUARD`: Automatically unlocks and enters the device.
    *   `FLAG_GRANT_TRUST_TEMPORARY_AND_RENEWABLE`: Trust is granted but may be revoked by the system (e.g., on screen off), allowing the agent to re-grant it without a PIN.
*   **`revokeTrust()`**: Immediately ends the trusted state.

### Escrow Tokens (Advanced)
*   **`addEscrowToken(byte[], UserHandle)`**: Provides a cryptographic token that can be used to derive a "synthetic password," enabling the agent to unlock File-Based Encryption (FBE) storage.
*   **`unlockUserWithToken(handle, token, user)`**: Attempts to unlock the user's encrypted storage using a previously registered escrow token.

### Lifecycle Callbacks
*   **`onUnlockAttempt(boolean)`**: Notifies the agent when the user successfully or unsuccessfully tries to unlock via PIN/Pattern.
*   **`onDeviceLocked()` / `onDeviceUnlocked()`**: Notifies the agent of the current keyguard state.
*   **`onTrustTimeout()`**: Called when the duration specified in `grantTrust` expires.

## API Reference

### Constants
*   `SERVICE_INTERFACE`: `"android.service.trust.TrustAgentService"`
*   `TRUST_AGENT_META_DATA`: `"android.service.trust.trustagent"`

## Java-to-C++ Translation Guide

### IPC
*   **Java**: `ITrustAgentService.Stub`.
*   **C++**: `BnTrustAgentService`.
*   **Callback Proxy**: Uses `ITrustAgentServiceCallback` to communicate with `TrustManagerService`.

### Security
*   Escrow tokens (`byte[]`) are highly sensitive cryptographic material. In C++, these must be handled with extreme care, ideally using `mlock` to prevent swapping to disk and zeroing out memory immediately after use.
*   The implementation of the actual trust logic (e.g., Bluetooth scanning) often resides in a separate process or uses system-level scanning APIs.

## Implementation Risks
*   **Security Vulnerability**: A bug in a trust agent can allow unauthorized access to the device.
*   **Power Consumption**: Agents that scan for Bluetooth or GPS must be power-efficient to avoid draining the battery while the device is "locked."
*   **Escrow Token Failure**: If the escrow token management fails, the user may be unable to access their data after a reboot (if the agent is the primary unlock method).
