# KeyChainProtectionParams - Reverse Engineering Documentation

## Executive Summary
`KeyChainProtectionParams` describes how a KeyChain Snapshot is protected (typically via the user's lock screen). It includes the secret type, UI format, key derivation parameters, and the secret itself.

## Architecture Overview
*   **Package**: `android.security.keystore.recovery`
*   **Type**: Class (Parcelable, System API)

## Data Model
*   `mUserSecretType` (int): E.g., `TYPE_LOCKSCREEN` (100).
*   `mLockScreenUiFormat` (int): PIN, Pattern, or Password.
*   `mKeyDerivationParams`: Algorithm and salt.
*   `mSecret` (byte[]): The derived key/secret.

## Java-to-C++ Translation Guide
*   Simple struct.
*   **Security**: Note that `mSecret` contains sensitive data and should be handled with care (zeroized when done, though Java GC makes this hard). C++ allows better control (`memset_s` / `explicit_bzero`).
