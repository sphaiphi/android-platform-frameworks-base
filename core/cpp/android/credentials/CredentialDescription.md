# CredentialDescription - Reverse Engineering Documentation

## Executive Summary
`CredentialDescription` describes a credential that is actively provisioned on the device. It is used by providers to register their available credentials with the system, allowing the system to filter and route requests efficiently without waking up every provider.

## Architecture Overview
- **Type**: Parcelable Data Class (Immutable).
- **Usage**: Used in `RegisterCredentialDescriptionRequest`.

## Detailed Functionality

### Core Fields
- `mType` (String): The credential type (e.g., "PublicKeyCredential").
- `mSupportedElementKeys` (`Set<String>`): A set of keys/identifiers that this credential matches (e.g., usernames, user IDs). Used for filtering.
- `mCredentialEntries` (`List<CredentialEntry>`): UI entries to be displayed in the selector (e.g., "Sign in with John"). Note: `CredentialEntry` is in `android.service.credentials`.

### Constraints
- `MAX_ALLOWED_ENTRIES_PER_DESCRIPTION` = 16.
- `compareEntryTypes`: Validates that all `CredentialEntry` objects match the `mType`.

### Methods
- `getType()`
- `getSupportedElementKeys()`
- `getCredentialEntries()`
- `hashCode()` / `equals()`: Based on `type` and `supportedElementKeys` (Entries are excluded from identity).

## Java-Specific Notes
- **`Set<String>`**: Mapped to `std::vector<std::string>` or `std::unordered_set<std::string>` in C++.
- **`List<CredentialEntry>`**: Needs the `CredentialEntry` definition.

## Java-to-C++ Translation Guide
- **Limit Check**: Enforce the 16-entry limit in the constructor/factory.
- **Type Consistency**: Implement the validation logic checking entry types against the description type.
- **Equality**: Implement `operator==` ignoring the `entries` field, as per Java implementation.

## Data Model
```cpp
class CredentialDescription {
    std::string type;
    std::vector<std::string> supportedElementKeys;
    std::vector<CredentialEntry> credentialEntries; // Depends on CredentialEntry definition
};
```
