# CredentialProtectedWhileLockedViolation - Reverse Engineering Documentation

## Executive Summary
`CredentialProtectedWhileLockedViolation` is raised when a process attempts to access files in "Credential Protected" (CE) storage while the user is still locked (before they have entered their PIN/Pattern/Password). CE storage is encrypted and unavailable during this state.

## Architecture Overview
-   **Inheritance**: Extends `android.os.strictmode.Violation`.
-   **Context**: Part of Android's "Direct Boot" security model.

## Detailed Functionality
-   **Purpose**: Helps developers identify code that assumes user data is always available, which can cause app crashes or "missing data" bugs during device startup or while the device is in the background.
-   **Solution**: Developers should use `Device Protected` (DE) storage for data needed during the locked state.

## Java-to-C++ Translation Guide
-   **Native Mapping**: This violation is often detected in the VFS layer or the `system_server`'s file access checks.
