# PlatformVpnProfile.java - Reverse Engineering Documentation

## Executive Summary
`PlatformVpnProfile` is the abstract base class for all platform-managed VPN profiles (like IKEv2). It defines common properties and types for VPN configurations that the Android system can manage directly.

## Architecture Overview
- **Type**: Abstract Base Class
- **Package**: `android.net`
- **Subclasses**: `Ikev2VpnProfile`.
- **Relationship**: Higher-level abstraction over internal `VpnProfile`.

## Data Model
| Field | Type | Description |
| :--- | :--- | :--- |
| `mType` | `int` | VPN type (IKEv2 User/Pass, PSK, RSA). |
| `mExcludeLocalRoutes` | `boolean` | Whether to bypass VPN for local traffic. |
| `mRequiresInternetValidation` | `boolean` | Whether to require validation. |

## Functionality
-   `toVpnProfile()`: Abstract method to convert to the internal `VpnProfile`.
-   `fromVpnProfile()`: Static factory to create a specific subclass instance from an internal `VpnProfile`.

## Java-to-C++ Translation Guide
C++ base class.
```cpp
class PlatformVpnProfile {
public:
    int getType() const;
    bool areLocalRoutesExcluded() const;
    bool isInternetValidationRequired() const;
    virtual InternalVpnProfile toVpnProfile() const = 0;
protected:
    int mType;
    bool mExcludeLocalRoutes;
    bool mRequiresInternetValidation;
};
```
