# PersistentDataBlockManager - Reverse Engineering Documentation

## Executive Summary
`PersistentDataBlockManager` is a system service client used to manage a small, dedicated partition of persistent storage that survives a factory reset. This is primarily used for **Factory Reset Protection (FRP)** and managing the device's bootloader lock state.

## Architecture Overview
*   **System API**: Intended for use by system components like the setup wizard, settings, or authorized carrier/OEM apps.
*   **IPC**: Proxies calls to `IPersistentDataBlockService` in the system server.
*   **Hardware Dependency**: Relies on a specific "frp" or "persistent" partition defined in the device's partition table.
*   **Security**: Access is strictly limited by permissions and package name allow-listing.

## Detailed Functionality

### Core Data Operations
*   **`write(byte[])`**: Overwrites the entire persistent data block with the provided data.
*   **`read()`**: Retrieves the current content of the data block.
*   **`wipe()`**: Zeroes out the partition. Once wiped, further writes are blocked until the next reboot to prevent race conditions during factory reset.
*   **`getDataBlockSize()` / `getMaximumDataBlockSize()`**: Manage partition capacity.

### Bootloader Management (Legacy)
*   **`setOemUnlockEnabled(boolean)`**: Historically used to enable/disable bootloader unlocking. Now mostly deprecated in favor of `OemLockManager`.
*   **`getFlashLockState()`**: Returns the current state of the bootloader (LOCKED, UNLOCKED, UNKNOWN).

### Factory Reset Protection (FRP)
*   **`isFactoryResetProtectionActive()`**: Returns true if the device is currently locked due to an unauthorized factory reset.
*   **`deactivateFactoryResetProtection(byte[])`**: Attempts to unlock the device using a 32-byte secret matching the stored FRP secret.
*   **`setFactoryResetProtectionSecret(byte[])`**: Updates the FRP secret for future protection.

## API Reference

### Constants
*   `FLASH_LOCK_LOCKED` (1), `UNLOCKED` (0), `UNKNOWN` (-1).
*   `Context.PERSISTENT_DATA_BLOCK_SERVICE`: Service name for `Context.getSystemService()`.

## Java-to-C++ Translation Guide

### IPC
*   **Java**: `IPersistentDataBlockService.Stub.asInterface`.
*   **C++**: `sp<IPersistentDataBlockService>` obtained from `ServiceManager`.

### Storage
*   The system service implementation usually performs direct file I/O or `ioctl` calls on a block device (e.g., `/dev/block/platform/.../by-name/frp`). In C++, this involves standard `<fcntl.h>` and `<unistd.h>` operations (`open`, `read`, `write`, `fsync`).

## Implementation Risks
*   **Criticality**: Corruption of this block can lead to "bricked" devices or permanently active FRP.
*   **Atomicity**: Writing to the block device must be handled carefully (often using `fsync`) to ensure data is actually persisted before reporting success.
*   **Race Conditions**: The `wipe` logic explicitly blocks subsequent writes until reboot to ensure that a factory reset doesn't overwrite the wipe with stale data.
