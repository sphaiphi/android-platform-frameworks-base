# RecoverySystem - Reverse Engineering Documentation

## Executive Summary
`RecoverySystem` manages interactions with the recovery partition. It handles installing OTA updates, verifying package signatures, and wiping user data (Factory Reset). It communicates with the bootloader (BCB) to schedule recovery commands.

## Architecture Overview
-   **Role**: System Updater Client.
-   **Service**: `IRecoverySystem`.
-   **Files**:
    -   `command`: `/cache/recovery/command` (passed to bootloader).
    -   `uncrypt`: `/cache/recovery/uncrypt_file` (for processing encrypted data).

## Detailed Functionality

### OTA Installation (`installPackage`)
1.  **Uncrypt**: If the package is on `/data` (encrypted), calls `uncrypt` service to map the blocks to physical storage so recovery can read them.
2.  **BCB Setup**: Writes `--update_package=...` to the Bootloader Control Block.
3.  **Reboot**: Calls `PowerManager.reboot("recovery")`.

### Verification (`verifyPackage`)
-   Parses the PKCS#7 signature block (footer of the ZIP file).
-   Verifies it against trusted certificates (`/system/etc/security/otacerts.zip`).
-   Note: This runs in Java on the main system, *before* rebooting.

### Factory Reset (`rebootWipeUserData`)
-   **Wipe Options**: Can wipe `userdata`, `cache`, and even eSIM (`wipeEuiccData`).
-   **Broadcast**: Sends `MASTER_CLEAR_NOTIFICATION` to let apps prepare.
-   **Reboot**: Schedules `--wipe_data` in BCB and reboots.

## Java-to-C++ Translation Guide
-   **Uncrypt**: This is a native daemon interaction.
-   **BCB**: Requires writing to the `misc` partition. Android uses `libbootloader_message` for this.
-   **Verification**: Java uses `sun.security.pkcs`. C++ would use `openssl` or `boringssl`.

## Implementation Risks
-   **Bricking**: Corrupting the BCB can prevent the device from booting.
-   **Data Loss**: `rebootWipeUserData` is destructive.
