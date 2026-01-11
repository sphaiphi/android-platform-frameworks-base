# Registry Requests - Reverse Engineering Documentation

## Executive Summary
These classes manage the registration of active credentials for filtering purposes.

## 1. RegisterCredentialDescriptionRequest
- **Purpose**: Register a new active credential description.
- **Fields**: `mCredentialDescriptions` (`List<CredentialDescription>`).
- **Logic**: Can take a single description or a set in constructor.

## 2. UnregisterCredentialDescriptionRequest
- **Purpose**: Remove a previously registered credential description.
- **Fields**: `mCredentialDescriptions` (`List<CredentialDescription>`).

## Java-to-C++ Translation Guide
- **Container**: `std::vector<CredentialDescription>`.
- **Set/List**: Java uses `Set` in getters but `List` in Parceling. C++ should likely use `std::vector` for transport.

## Data Model
```cpp
struct RegisterCredentialDescriptionRequest {
    std::vector<CredentialDescription> descriptions;
};
```
