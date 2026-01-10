# RemoteLockscreenValidationResult - Reverse Engineering Documentation

## Executive Summary
`RemoteLockscreenValidationResult` is a data class used to communicate the outcome of a remote lock screen credential verification attempt. It provides status codes for various scenarios, including successful verification, invalid guesses, lockouts, session expirations, and situations where no more attempts are allowed.

## Architecture Overview
- **Core Components**:
    - `mResultCode`: Integer representing the specific outcome.
    - `mTimeoutMillis`: Delay before the next attempt can be made (used primarily for `RESULT_LOCKOUT`).
- **Inheritance**: Implements `Parcelable`.
- **Builder Pattern**: Uses an internal `Builder` class for construction.

## Detailed Functionality

### Result Codes
**Purpose**: Standardizing the outcomes of remote verification.
**Codes**:
- `RESULT_GUESS_VALID` (1): Success.
- `RESULT_GUESS_INVALID` (2): Incorrect credentials.
- `RESULT_LOCKOUT` (3): API throttled due to too many failures.
- `RESULT_NO_REMAINING_ATTEMPTS` (4): Hard limit reached.
- `RESULT_SESSION_EXPIRED` (5): Need to restart the validation flow.

### Construction
**Purpose**: Ensuring valid result objects.
**Mechanism**: The `Builder.build()` method enforces that a result code must be set before instantiation.

## API Reference
- `public int getResultCode()`: Returns the status code.
- `public long getTimeoutMillis()`: Returns the mandatory wait time.

## Java-to-C++ Translation Guide
- **Enum Mapping**: Map the result codes to a C++ `enum class`.
- **Data Structure**: Use a simple `struct` or a `class` with private members and public getters.
- **Parceling**: Implement standard `writeToParcel` and `readFromParcel` logic.

## Implementation Risks
- **Precision**: Ensure that `mTimeoutMillis` is handled as a 64-bit integer (`long` in Java, `int64_t` in C++).
- **Validation**: Replicate the "Result code must be set" check in the C++ constructor or builder.
