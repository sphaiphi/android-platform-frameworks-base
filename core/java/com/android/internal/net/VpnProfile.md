# VpnProfile - Reverse Engineering Documentation

## Executive Summary
`VpnProfile` is a storage class for VPN connection profiles. It supports both legacy VPN types (PPTP, L2TP, IPsec Xauth) and modern Platform VPN types (IKEv2/IPsec). It handles the custom serialization required for persistent storage in the Android Keystore.

## Architecture Overview
- **Storage**: Designed to be stored as a blob in the Keystore.
- **Serialization**: Uses a custom `encode()`/`decode()` logic based on a null-character delimiter (`\0`) for backward compatibility.
- **Hierarchy**: Acts as the persistent peer to `android.net.PlatformVpnProfile`.

## Detailed Functionality

### Custom Serialization
**Purpose**: To persist profiles across Android version upgrades without using standard Parcelable blobs (which can be unstable for long-term storage).
**Algorithm**:
- `encode()`: Joins all fields into a single `\0`-delimited string.
- `decode()`: Splits the string and parses fields back into their respective types.

### Support for IKEv2
**Purpose**: To provide a modern, secure VPN backend.
- Supports `IkeTunnelConnectionParams` for complex IKEv2 configurations.
- Handles inline authentication parameters (Private Keys, Certificates).

### Validation
**Purpose**: To ensure the profile is safe for features like "Always-on VPN" (Lockdown mode).
**Criteria**:
- Server must be a numeric IP (to avoid DNS dependency during boot).
- DNS must be specified and numeric.
- PPTP is specifically disallowed for lockdown due to security vulnerabilities.

## Data Model

### Members
- `key` (`String`): The alias used in the Keystore.
- `name` (`String`): User-friendly profile name.
- `type` (`int`): One of `TYPE_PPTP`, `TYPE_IKEV2_IPSEC_PSK`, etc.
- `server` (`String`): Hostname or IP.
- `ipsecSecret` (`String`): PSK or Private Key.
- `proxy` (`ProxyInfo`): HTTP proxy settings for the VPN.

## API Reference (Internal)

### Key Types
- `TYPE_IKEV2_IPSEC_USER_PASS` (6)
- `TYPE_IKEV2_IPSEC_PSK` (7)
- `TYPE_IKEV2_IPSEC_RSA` (8)

### Methods
- `byte[] encode()`: Serialize to bytes.
- `VpnProfile decode(String key, byte[] value)`: Reconstruct from bytes.
- `boolean isValidLockdownProfile()`: Check if suitable for boot-time blocking.

## Java-to-C++ Translation Guide

### Delimiter Parsing
- **Java**: `split(VALUE_DELIMITER, -1)`.
- **C++**: Use `std::getline` with a custom delimiter or `boost::split`. Note that `\0` is a tricky delimiter in C-style strings; ensure you use `std::string` which handles embedded nulls.

### Cryptographic Keys
- **Java**: RSA keys are stored as PKCS#8 strings.
- **C++**: Use `OpenSSL` or `BoringSSL` to parse these strings into `EVP_PKEY` objects.

## Test Cases & Validation
1. **Migration Test**: Encode a profile on an older version's logic (simulated) and verify `decode()` handles the smaller field count correctly (providing defaults).
2. **Lockdown Validation**: Verify that a profile with a hostname (e.g., "vpn.example.com") returns `false` for `isValidLockdownProfile()`.
3. **Delimiter Integrity**: Verify that a password containing a comma or other special characters (but not `\0`) is correctly preserved through the encode/decode cycle.

## Implementation Risks
- **Keystore Interaction**: Profiles are stored in the system Keystore. The C++ implementation must have the correct permissions to access the `VPN` namespace in Keystore.
- **Backward Compatibility**: The order of fields in the `encode()` string is fixed. Any new fields MUST be appended to the end to avoid breaking older decoders.
