# RecoveryController - Reverse Engineering Documentation

## Executive Summary
`RecoveryController` is the main API for the Recoverable KeyStore. It allows apps (specifically the "Recovery Agent") to initialize recovery, generate snapshots, and restore keys.

## Architecture Overview
*   **Package**: `android.security.keystore.recovery`
*   **Type**: Class (System API)
*   **Service Name**: `lock_settings` (via `ILockSettings` Binder interface).

## Detailed Functionality

### 1. Initialization
*   **Method**: `initRecoveryService`
*   **Purpose**: Configures the root of trust and the list of available remote trusted hardware certificates.

### 2. Snapshot Management
*   **Method**: `getKeyChainSnapshot`
*   **Method**: `setSnapshotCreatedPendingIntent`
*   **Method**: `setServerParams`
*   **Method**: `setRecoverySecretTypes`
*   **Purpose**: managing the creation and retrieval of KeyChain snapshots.

### 3. Key Management
*   **Method**: `generateKey` / `importKey`
*   **Purpose**: Creates/Imports keys that are marked as "Recoverable".
*   **Method**: `getKey`
*   **Purpose**: Retrieves a key.
*   **Method**: `removeKey`
*   **Method**: `getAliases`
*   **Method**: `setRecoveryStatus` / `getRecoveryStatus`

### 4. Recovery Session
*   **Method**: `createRecoverySession`
*   **Purpose**: Starts a session to recover keys.

## Java-to-C++ Translation Guide
*   This is a client-side wrapper around `ILockSettings`. The heavy lifting is in the system server (LockSettingsService).
*   The C++ implementation would primarily be the server-side logic handling these IPC calls.
