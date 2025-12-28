# RemoteLockscreenValidationSession - Reverse Engineering Documentation

## Executive Summary
`RemoteLockscreenValidationSession` provides the necessary metadata to perform a remote lock screen credentials check. It specifies the type of lock (password, PIN, pattern), contains the source's public key for secure communication, and tracks the number of remaining attempts allowed for the session.

## Architecture Overview
- **Structure**:
    - `mLockType`: Format of the credentials (from `KeyguardManager.LockTypes`).
    - `mSourcePublicKey`: A byte array containing the public key using secure box encoding.
    - `mRemainingAttempts`: Integer tracking the retry budget.
- **Inheritance**: Implements `Parcelable`.
- **Builder Pattern**: Uses an internal `Builder` class for configuration.

## Detailed Functionality

### Secure Communication
**Purpose**: Protecting sensitive credentials.
**Logic**: The `mSourcePublicKey` is a mandatory field. It is used to encrypt the credentials before they are transmitted back to the source device for validation.

### Retry Budget
**Purpose**: Preventing brute-force attacks.
**Logic**: `mRemainingAttempts` allows the validator to inform the user how many more tries they have before a lockout or session reset occurs.

## API Reference
- `public int getLockType()`: Returns the UI format (PIN/Pattern/Password).
- `public byte[] getSourcePublicKey()`: Returns the encryption key.
- `public int getRemainingAttempts()`: Returns the retry count.

## Java-to-C++ Translation Guide
- **Key Storage**: Map the byte array to `std::vector<uint8_t>`.
- **Lock Types**: Use the native `android::app::KeyguardManager` constants for lock types.
- **Parceling**: Implement `writeToParcel` and `readFromParcel`, ensuring the byte array length is correctly marshalled.

## Implementation Risks
- **Data Integrity**: The `mSourcePublicKey` must be preserved exactly. Any corruption during parceling will cause encryption/decryption failures.
- **Attempt Tracking**: The `mRemainingAttempts` must be updated consistently between the validating service and the client UI.
