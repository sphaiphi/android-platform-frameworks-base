# KeyChainSnapshot - Reverse Engineering Documentation

## Executive Summary
`KeyChainSnapshot` represents a backup of the keystore. It contains encrypted application keys, protection parameters, and metadata needed to restore the keys on another device.

## Architecture Overview
*   **Package**: `android.security.keystore.recovery`
*   **Type**: Class (Parcelable, System API)

## Data Model
*   `mSnapshotVersion` (int).
*   `mMaxAttempts` (int): Max guesses for lock screen.
*   `mCounterId` (long).
*   `mServerParams` (byte[]): Identifier for the device/snapshot on the server.
*   `mCertPath` (RecoveryCertPath): Public key of the trusted hardware used to encrypt the recovery key.
*   `mKeyChainProtectionParams`: List of protection methods.
*   `mEntryRecoveryData`: List of `WrappedApplicationKey` (the actual keys).
*   `mEncryptedRecoveryKeyBlob` (byte[]): The "Recovery Key", encrypted with the user's lock screen and the remote hardware's public key.

## Java-to-C++ Translation Guide
*   Complex struct containing lists and blobs.
*   Core component of the "Recoverable KeyStore" protocol.
