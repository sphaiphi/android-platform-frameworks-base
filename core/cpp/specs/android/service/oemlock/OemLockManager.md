# OemLockManager - Reverse Engineering Documentation

## Executive Summary
`OemLockManager` is a system service client that provides an interface for managing the OEM lock state of the device. It determines whether the bootloader is allowed to be unlocked, requiring agreement from both the carrier and the user.

## Architecture Overview
*   **System API**: Marked with `@SystemApi`, intended for use by system-level apps (like Settings or carrier apps).
*   **IPC**: Proxies calls to `IOemLockService` implemented in the system server.
*   **Agreement Model**: Unlocking the bootloader requires:
    1.  Carrier permission (`isOemUnlockAllowedByCarrier`).
    2.  User permission (`isOemUnlockAllowedByUser`).
    3.  Hardware capability (`isOemUnlockAllowed`).

## Detailed Functionality

### Operations
*   **`getLockName()`**: Identifies the vendor-specific security protocol for the OEM lock.
*   **`setOemUnlockAllowedByCarrier(boolean, byte[])`**: Updates the carrier's opinion on unlocking. May require a signed blob (`signature`) to verify legitimate carrier intent.
*   **`setOemUnlockAllowedByUser(boolean)`**: Updates the user's opinion (typically controlled via "OEM unlocking" in Developer Options).
*   **`isDeviceOemUnlocked()`**: Returns the actual current status of the hardware (whether the bootloader is currently unlocked).

### Permissions
*   `MANAGE_CARRIER_OEM_UNLOCK_STATE`: Required for carrier-level operations.
*   `MANAGE_USER_OEM_UNLOCK_STATE`: Required for user-level operations.

## API Reference

### Constants
*   `Context.OEM_LOCK_SERVICE`: The name of the service for `Context.getSystemService()`.

## Java-to-C++ Translation Guide

### IPC
*   **Java**: `IOemLockService.Stub.asInterface`.
*   **C++**: `sp<IOemLockService>` obtained from `ServiceManager`.

### Security
*   The `byte[] signature` in `setOemUnlockAllowedByCarrier` must be passed through to the HAL layer securely.

## Implementation Risks
*   **Security**: OEM unlocking is a high-security operation. This service is a gatekeeper for bootloader integrity.
*   **HAL Dependency**: The system service implementation of `IOemLockService` typically communicates with a vendor HAL (e.g., `android.hardware.oemlock`).
