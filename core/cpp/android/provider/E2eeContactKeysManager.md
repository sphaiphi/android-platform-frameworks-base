# E2eeContactKeysManager - Reverse Engineering Documentation

## Executive Summary
`E2eeContactKeysManager` provides access to end-to-end encryption (E2EE) keys for contacts. It manages self keys (for the local user) and contact keys (public keys of others).

## Architecture Overview
- **Authority**: `com.android.contactkeys.contactkeysprovider`.
- **Dependencies**: `ContentResolver`.

## Detailed Functionality
-   **Operations**: Insert, Update, Retrieve, Remove, Update Verification State.
-   **Keys**:
    -   `E2eeContactKey`: Device ID, Account ID, Owner Package, Key Value, Verification States.
    -   `E2eeSelfKey`: Similar structure for self.
-   **Verification**: Local (QR code) vs Remote (Key Transparency) verification states.

## Data Model
-   **E2eeContactKeys**: Column definitions (`lookup_key`, `device_id`, `key_value`, etc.).

## Java-to-C++ Translation Guide
-   **ContentProvider Calls**: Wraps `ContentResolver.call`.
-   **Parcels**: Returns Lists of Parcelable objects (`E2eeContactKey`).
