# UnregisterCredentialDescriptionRequest - Reverse Engineering Documentation

## Executive Summary
Request to unregister a previously registered `CredentialDescription`.

## Architecture Overview
- **Type**: Parcelable Data Class (Immutable).
- **Role**: Input to `CredentialManager.unregisterCredentialDescription`.

## Detailed Functionality
- **`mCredentialDescriptions` (`List<CredentialDescription>`)**: The descriptions to unregister.

## Java-to-C++ Translation Guide
- **Container**: `std::vector<CredentialDescription>`.

## Data Model
```cpp
struct UnregisterCredentialDescriptionRequest {
    std::vector<CredentialDescription> descriptions;
};
```
