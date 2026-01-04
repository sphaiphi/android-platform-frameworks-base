# RecoverySession - Reverse Engineering Documentation

## Executive Summary
`RecoverySession` represents a session to recover a `KeyChainSnapshot` from remote storage. It handles the cryptographic handshake (Recovery Claim) and the decryption of restored keys.

## Architecture Overview
*   **Package**: `android.security.keystore.recovery`
*   **Type**: Class (System API)
*   **Dependencies**: `RecoveryController`.

## Detailed Functionality

### 1. Start Session
*   **Method**: `start`
*   **Purpose**: Initiates recovery. Generates a session ID and a blob containing the "Recovery Claim" (proof of user secret possession + session key params).
*   **Returns**: The recovery claim blob to be sent to the remote server.

### 2. Recover Keys
*   **Method**: `recoverKeyChainSnapshot`
*   **Purpose**: Takes the response from the remote server (which contains the Recovery Key encrypted with the session key) and the list of wrapped application keys.
*   **Logic**: Calls `recoverKeyChainSnapshot` on the binder. The service decrypts the recovery key, then decrypts the app keys, and imports them into Keystore.
*   **Returns**: Map of aliases to `Key` objects.

### 3. Close
*   **Method**: `close`
*   **Purpose**: Cleans up session resources on the server.

## Java-to-C++ Translation Guide
*   Client wrapper around Binder calls.
