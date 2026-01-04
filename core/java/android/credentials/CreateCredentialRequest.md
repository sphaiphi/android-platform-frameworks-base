# CreateCredentialRequest - Reverse Engineering Documentation

## Executive Summary
`CreateCredentialRequest` encapsulates the data required to register (create) a new credential. Unlike `GetCredentialRequest` which can ask for multiple types, a creation request targets a specific credential type.

## Architecture Overview
- **Type**: Parcelable Data Class (Immutable).
- **Role**: Input to `CredentialManager.createCredential`.

## Detailed Functionality

### Core Fields
- `mType` (String): The type of credential to create.
- `mCredentialData` (Bundle): Full creation data (secrets, metadata).
- `mCandidateQueryData` (Bundle): Partial data for provider query phase.
- `mIsSystemProviderRequired` (boolean): Constraint for system providers.
- `mAlwaysSendAppInfoToProvider` (boolean): Privacy flag.
- `mOrigin` (String): Origin of the caller.

### Methods
- Getters for all fields.
- Builder pattern.

## Java-Specific Notes
- **Single Type**: Unlike Get, Create is single-type.
- **Two-Phase Data**: Explicit separation of `CredentialData` (Full) and `CandidateQueryData` (Partial) is enforced for privacy.

## Java-to-C++ Translation Guide
- **Structure**:
```cpp
struct CreateCredentialRequest {
    std::string type;
    android::os::Bundle credentialData;
    android::os::Bundle candidateQueryData;
    bool isSystemProviderRequired;
    bool alwaysSendAppInfoToProvider;
    std::optional<std::string> origin;
};
```
