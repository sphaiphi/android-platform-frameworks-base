# Ikev2VpnProfile.java - Reverse Engineering Documentation

## Executive Summary
`Ikev2VpnProfile` is a configuration class for IKEv2/IPsec VPNs. It allows applications to provision VPN profiles that the Android platform can manage natively, without requiring the app to maintain a background service. It supports various authentication methods (User/Pass, PSK, RSA Digital Signature) and configuration options (Proxy, MTU, Allowed Algorithms).

## Architecture Overview
- **Type**: Configuration Object (Immutable)
- **Package**: `android.net`
- **Extends**: `PlatformVpnProfile`
- **Design Pattern**: Builder Pattern (`Ikev2VpnProfile.Builder`).
- **Key Dependencies**:
    -   `android.net.ipsec.ike.*`: For IKEv2 specific parameters (`IkeTunnelConnectionParams`).
    -   `java.security.cert.X509Certificate`: For certificate-based auth.
    -   `java.security.PrivateKey`: For RSA auth.
    -   `android.net.ProxyInfo`: For HTTP proxy settings.

## Detailed Functionality

### Authentication Types
The profile supports three main authentication modes, defined in `PlatformVpnProfile`:
1.  **User/Password** (`TYPE_IKEV2_IPSEC_USER_PASS`): EAP-MSCHAPv2 typically.
2.  **Pre-Shared Key** (`TYPE_IKEV2_IPSEC_PSK`).
3.  **RSA Digital Signature** (`TYPE_IKEV2_IPSEC_RSA`): Uses X.509 user certificate and private key.

### Configuration Parameters
-   **Server Address**: Hostname or IP.
-   **User Identity**: IKEv2 identity (FQDN, RFC822, KeyID, IPv4/6).
-   **MTU**: Maximum Transmission Unit (min 1280 for IPv6 compliance).
-   **Algorithms**: Allowed IPsec algorithms (Crypt, Auth, AEAD). Defaults to a secure set, explicitly bans insecure ones (MD5, SHA1) unless legacy/custom.
-   **Bypassable**: Whether other apps can bypass the VPN.
-   **Metered**: Whether the VPN interface is treated as metered.
-   **Proxy**: Optional HTTP proxy.
-   **Automatic NATT/IP Version**: Flags to let the platform handle NAT-T keepalives and IP family selection.

### Validation
-   Ensures required fields are present for the selected auth type.
-   Validates MTU >= 1280.
-   Validates allowed algorithms (must have encryption + auth or AEAD).
-   Checks for insecure algorithms.

### Serialization (`toVpnProfile`)
Converts the high-level `Ikev2VpnProfile` into an internal `VpnProfile` object used by the system server. Handles encoding of keys/certs (PEM format, Base64).
-   **Keys**: Encoded to Base64 strings.
-   **Certificates**: Converted to PEM strings.
-   **Prefixes**: Uses prefixes like `INLINE:` or `KEYSTORE_ALIAS:` to hint storage location of private keys.

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mServerAddr` | `String` | VPN Server address. |
| `mUserIdentity` | `String` | IKE Identity. |
| `mPresharedKey` | `byte[]` | PSK (if applicable). |
| `mServerRootCaCert` | `X509Certificate` | Server Root CA (optional). |
| `mUsername`/`mPassword` | `String` | Credentials for User/Pass auth. |
| `mRsaPrivateKey` | `PrivateKey` | Client private key for RSA auth. |
| `mUserCert` | `X509Certificate` | Client certificate for RSA auth. |
| `mAllowedAlgorithms` | `List<String>` | List of accepted crypto algorithms. |
| `mIkeTunConnParams` | `IkeTunnelConnectionParams` | Low-level IKE params (alternative to top-level fields). |

## Java-to-C++ Translation Guide

### Class Definition
A C++ class or struct with a Builder.

```cpp
class Ikev2VpnProfile : public PlatformVpnProfile {
public:
    enum AuthType { USER_PASS, PSK, RSA };
    
    struct Builder;

    // Getters
    std::string getServerAddr() const;
    std::string getUserIdentity() const;
    // ...
    
private:
    std::string mServerAddr;
    std::string mUserIdentity;
    std::vector<uint8_t> mPresharedKey;
    // Certificates/Keys would likely be OpenSSL/BoringSSL types or raw bytes (PEM/DER)
    std::string mUsername;
    std::string mPassword;
    // ...
};
```

### Cryptography
-   Java uses `java.security` interfaces. C++ implementation will likely use `libcrypto` (BoringSSL) or `libssl`.
-   Translation of `X509Certificate` -> PEM string is required for compatibility with legacy `VpnProfile` serialization if that path is maintained.

### Validation Logic
-   Port `validateAllowedAlgorithms` strictly.
-   Port `validate()` method to ensure mandatory fields.

### KeyStore Integration
-   Java code references `AndroidKeyStore`. C++ access to Keystore keys is different (usually via Keystore2 AIDL interfaces or Engine). The `PREFIX_KEYSTORE_ALIAS` string logic indicates legacy behavior where the alias is passed around.

## Test Cases
1.  **Builder Validation**: Missing server address -> Throw.
2.  **Algorithm Validation**: Empty list -> Throw. List with only AES-CBC (no auth) -> Throw. List with AES-GCM -> OK.
3.  **MTU**: Set < 1280 -> Throw.
4.  **Auth Types**:
    -   User/Pass: Missing user or pass -> Throw.
    -   PSK: Missing PSK -> Throw.
    -   RSA: Missing User Cert or Private Key -> Throw.
