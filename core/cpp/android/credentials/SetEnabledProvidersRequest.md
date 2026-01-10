# Settings Requests - Reverse Engineering Documentation

## Executive Summary
Classes used by settings applications to configure the Credential Manager.

## 1. SetEnabledProvidersRequest
- **Purpose**: Update the list of enabled providers.
- **Fields**: `mProviders` (`List<String>`): List of flattened component names.

## 2. ListEnabledProvidersResponse
- **Purpose**: Return the list of enabled providers.
- **Fields**: `mProviders` (`List<String>`).

## Java-to-C++ Translation Guide
- **Strings**: Represents ComponentNames.
- **Collection**: `std::vector<std::string>`.

## Data Model
```cpp
struct SetEnabledProvidersRequest {
    std::vector<std::string> provider_component_names;
};
```
