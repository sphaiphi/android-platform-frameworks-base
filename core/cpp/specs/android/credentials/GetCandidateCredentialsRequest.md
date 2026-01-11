# GetCandidateCredentialsRequest - Reverse Engineering Documentation

## Executive Summary
`GetCandidateCredentialsRequest` is a hidden API request used to retrieve credential candidates, primarily for Autofill integration.

## Architecture Overview
- **Type**: Parcelable Data Class (Immutable).
- **Role**: Input to `CredentialManager.getCandidateCredentials`.

## Detailed Functionality
- **`mCredentialOptions` (`List<CredentialOption>`)**: The options to query.
- **`mData` (Bundle)**: Global request data.
- **`mOrigin` (String)**: Calling app origin.

## Java-to-C++ Translation Guide
- **List**: `std::vector<CredentialOption>`.
- **Bundle**: `android::os::Bundle`.
- **Origin**: `std::optional<std::string>`.

## Data Model
```cpp
struct GetCandidateCredentialsRequest {
    std::vector<CredentialOption> credential_options;
    android::os::Bundle data;
    std::optional<std::string> origin;
};
```
