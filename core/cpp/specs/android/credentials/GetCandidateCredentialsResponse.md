# GetCandidateCredentialsResponse - Reverse Engineering Documentation

## Executive Summary
`GetCandidateCredentialsResponse` contains the list of candidate credentials found by providers, returned to the system (Autofill).

## Architecture Overview
- **Type**: Parcelable Data Class (Immutable).
- **Role**: Output of `CredentialManager.getCandidateCredentials`.

## Detailed Functionality
- **`mCandidateProviderDataList` (`List<GetCredentialProviderData>`)**: List of provider data containing entries. Note: `GetCredentialProviderData` is in the `selection` package.
- **`mIntent` (Intent)**: Intent to launch the selector UI if needed.
- **`mPrimaryProviderComponentName` (`ComponentName`)**: The primary provider, if any.

## Java-to-C++ Translation Guide
- **Data List**: Requires `GetCredentialProviderData` definition.
- **Intent**: `android::content::Intent`.
- **ComponentName**: `android::content::ComponentName`.

## Data Model
```cpp
struct GetCandidateCredentialsResponse {
    std::vector<GetCredentialProviderData> candidate_provider_data_list;
    android::content::Intent intent;
    std::optional<android::content::ComponentName> primary_provider_component_name;
};
```
