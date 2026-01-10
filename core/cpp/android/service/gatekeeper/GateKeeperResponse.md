# GateKeeperResponse - Reverse Engineering Documentation

## Executive Summary
`GateKeeperResponse` is a Parcelable data class that encapsulates the result of a credential verification request handled by the GateKeeper service. It conveys whether the verification succeeded, failed with a retry timeout, or encountered an error.

## Data Model

### Fields
*   `mResponseCode`: `int` - The outcome of the verification.
    *   `RESPONSE_OK` (0): Success.
    *   `RESPONSE_RETRY` (1): Verification failed; user must wait before retrying.
    *   `RESPONSE_ERROR` (-1): Generic failure.
*   `mTimeout`: `int` - The number of milliseconds to wait before retrying (only valid if code is `RESPONSE_RETRY`).
*   `mPayload`: `byte[]` - The Hardware Authentication Token (HAT) returned on success, used to prove authentication to other system components (like KeyStore).
*   `mShouldReEnroll`: `boolean` - Indicates if the credential should be re-enrolled (e.g., to upgrade the underlying cryptographic format).

## API Reference

### Factory Methods (Static)
*   `createGenericResponse(int code)`
*   `createRetryResponse(int timeout)`
*   `createOkResponse(byte[] payload, boolean shouldReEnroll)`

### Getters
*   `getResponseCode()`
*   `getTimeout()`
*   `getPayload()`
*   `getShouldReEnroll()`

## Java-to-C++ Translation Guide

### Parcelable
*   **Java**: Custom serialization based on the response code.
    *   `OK`: Writes `shouldReEnroll` (int), then size + byte array.
    *   `RETRY`: Writes `timeout` (int).
    *   `ERROR`: Only writes the code.
*   **C++**: `android::Parcelable`. The `writeToParcel` and `readFromParcel` logic must match the branching structure of the Java version to maintain compatibility with the system server.

### Constants
*   The constants `RESPONSE_ERROR`, `OK`, and `RETRY` should be mapped to an `enum class` in C++.

## Implementation Notes
*   **Immutable Pattern**: The object is immutable once created.
*   **HAT Payload**: The `mPayload` is a sensitive binary blob. In C++, this is typically handled as a `std::vector<uint8_t>`.
