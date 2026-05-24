# ListEnabledProvidersResponse - Reverse Engineering Documentation

## Executive Summary
Response containing the list of enabled providers.

## Architecture Overview
- **Type**: Parcelable Data Class (Immutable).
- **Role**: Output of `CredentialManager.getCredentialProviderServices` (implied or internal usage).

## Detailed Functionality
- **`mProviders` (`List<String>`)**: List of flattened component names of enabled providers.

## Java-to-C++ Translation Guide
- **Container**: `std::vector<std::string>`.

## Data Model
```cpp
struct ListEnabledProvidersResponse {
    std::vector<std::string> provider_component_names;
};
```
