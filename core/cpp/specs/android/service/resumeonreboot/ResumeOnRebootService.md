# ResumeOnRebootService - Reverse Engineering Documentation

## Executive Summary
`ResumeOnRebootService` is a system service base class used to manage sensitive cryptographic blobs across a device reboot. This is a critical component of the **Resume on Reboot** feature, which allows OTA updates to reboot the device and automatically unlock user data encryption (DE) without requiring the user to manually enter their PIN/Password immediately after the restart.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC**: Implements `IResumeOnRebootService.Stub`.
*   **Threading**: Uses a `BackgroundThread` handler to perform wrap/unwrap operations, avoiding blocking the binder thread.
*   **Permission**: Requires `android.permission.BIND_RESUME_ON_REBOOT_SERVICE`.
*   **Deployment**: The service must be marked as `directBootAware="true"` in the manifest because `onUnwrap` is called before the user first unlocks the device.

## Detailed Functionality

### Core Operations
*   **`onWrap(byte[] blob, long lifeTimeInMillis)`**:
    *   **Goal**: Securely wrap (encrypt) a ~100-byte secret blob.
    *   **Lifetime**: The implementation MUST ensure the blob cannot be unwrapped after the specified expiration time.
    *   **Requirement**: Should use tamper-resistant hardware (Secure Element) or a remote server to manage the encryption and the secure clock.
*   **`onUnwrap(byte[] wrappedBlob)`**:
    *   **Goal**: Decrypt and return the original secret blob.
    *   **Context**: Executed after reboot while the device is in Direct Boot mode.

### IPC Dispatches
*   **`wrapSecret`**: Dispatches to `onWrap`. Results (wrapped blob or exception) are sent back via `RemoteCallback`.
*   **`unwrap`**: Dispatches to `onUnwrap`. Results are sent back via `RemoteCallback`.

## API Reference

### Constants
*   `SERVICE_INTERFACE`: `"android.service.resumeonreboot.ResumeOnRebootService"`

## Java-to-C++ Translation Guide

### Data Structures
*   Blobs are `byte[]`, mapping to `std::vector<uint8_t>`.
*   `RemoteCallback` is used for asynchronous results.

### Security
*   The C++ implementation of the actual wrapping logic typically resides in a HAL (Hardware Abstraction Layer) or a TEE (Trusted Execution Environment) application.
*   The `ResumeOnRebootService` acts as the framework-level entry point to these secure components.

## Implementation Risks
*   **Critical Path**: Failure to unwrap correctly prevents the device from automatically resuming after an update, requiring manual user intervention.
*   **Security**: If the lifetime is not strictly enforced, an attacker who obtains the wrapped blob might be able to decrypt it long after the intended reboot window.
*   **Network Dependency**: If using a remote server for wrapping, the device must have a reliable network connection during the OTA preparation phase.
