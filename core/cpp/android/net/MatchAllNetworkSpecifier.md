# MatchAllNetworkSpecifier.java - Reverse Engineering Documentation

## Executive Summary
`MatchAllNetworkSpecifier` is a marker class used in `NetworkRequests` to indicate that the request can be satisfied by *any* network specifier. It is primarily used by `NetworkFactory` instances.

## Architecture Overview
- **Type**: Marker Class / `Parcelable`
- **Package**: `android.net`
- **Extends**: `NetworkSpecifier`
- **Usage**: Internal framework signaling.

## detailed Functionality
-   **Validation**: Throws `IllegalStateException` if `canBeSatisfiedBy` is called, ensuring it's not used in a typical `NetworkRequest` matching flow against concrete networks in a way that implies restriction. It's a "wildcard" for offering networks, not requesting them (based on comments).
-   **Serialization**: Stateless (Parcelable writes nothing).

## Java-to-C++ Translation Guide
A simple empty struct/class with a unique type identifier is sufficient.

```cpp
class MatchAllNetworkSpecifier : public NetworkSpecifier {
    // Empty
};
```
