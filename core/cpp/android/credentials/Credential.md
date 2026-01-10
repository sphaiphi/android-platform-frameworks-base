# Credential - Reverse Engineering Documentation

## Executive Summary
`Credential` is a data class representing a successfully retrieved user credential. It acts as a generic container holding a type identifier and a `Bundle` of data specific to that credential type (e.g., Password, Passkey).

## Architecture Overview
- **Type**: Parcelable Data Class (Immutable).
- **Role**: Return value for `GetCredentialResponse`.

## Detailed Functionality

### Core Fields
- `mType` (String): Identifies the specific credential type (e.g., `Credential.TYPE_PASSWORD_CREDENTIAL`).
- `mData` (Bundle): Key-value pairs containing the actual credential secrets or metadata (e.g., username, password, authentication token).

### Methods
- `getType()`: Returns the type string.
- `getData()`: Returns the data Bundle.
- `writeToParcel(...)`: Serialization logic.

## Java-Specific Notes
- **`Bundle`**: A flexible, loosely typed container.
- **Immutability**: Fields are `final`, enforcing thread safety and predictability.

## Java-to-C++ Translation Guide
- **Class Structure**: Simple C++ struct or class with accessors.
- **Bundle**: Map to `android::os::Bundle` (C++ implementation exists).
- **Parcelable**: Implement `Parcelable` interface (read/write from `Parcel`).
- **Type Safety**: The `mData` is untyped in Java. C++ might expose it as `android::os::Bundle`.

## Data Model
```cpp
struct Credential {
    std::string type;
    android::os::Bundle data;
};
```
