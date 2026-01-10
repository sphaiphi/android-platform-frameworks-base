# CredentialOption - Reverse Engineering Documentation

## Executive Summary
`CredentialOption` represents a specific request requirement within a `GetCredentialRequest`. It specifies the type of credential requested, along with the request data and constraints (e.g., allowed providers).

## Architecture Overview
- **Type**: Parcelable Data Class (Immutable).
- **Role**: Part of `GetCredentialRequest`.

## Detailed Functionality

### Core Fields
- `mType` (String): The requested credential type.
- `mCredentialRetrievalData` (Bundle): Full request parameters sent to the provider if selected.
- `mCandidateQueryData` (Bundle): Partial request parameters sent to providers during the query phase (privacy-preserving).
- `mIsSystemProviderRequired` (boolean): If true, only system providers are queried.
- `mAllowedProviders` (`ArraySet<ComponentName>`): specific list of providers to query. If empty, follows default discovery rules.

### Constants
- `SUPPORTED_ELEMENT_KEYS`: Key used in Bundles to pass filtering keys.

### Methods
- Getters for all fields.
- `writeToParcel`: Serialization.

## Java-Specific Notes
- **`ArraySet`**: Optimized Android collection. Map to `std::vector` or `std::set` in C++.
- **`ComponentName`**: Standard Android identifier.
- **Privacy Design**: Distinct `CredentialRetrievalData` vs `CandidateQueryData` is a key privacy feature. C++ API must preserve this distinction.

## Java-to-C++ Translation Guide
- **Bundles**: `android::os::Bundle`.
- **System Provider Logic**: Boolean flag `isSystemProviderRequired`.
- **Allowed Providers**: `std::vector<android::content::ComponentName>`.

## Data Model
```cpp
struct CredentialOption {
    std::string type;
    android::os::Bundle credentialRetrievalData;
    android::os::Bundle candidateQueryData;
    boolean isSystemProviderRequired;
    std::vector<ComponentName> allowedProviders;
};
```
