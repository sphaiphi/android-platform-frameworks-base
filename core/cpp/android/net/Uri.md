# Uri.java - Reverse Engineering Documentation

## Executive Summary
`Uri` is an abstract class representing an immutable URI reference (RFC 2396). It is the core Android class for manipulating URLs and URIs. It supports hierarchical (`http://google.com/path`) and opaque (`mailto:user@domain`) URIs. It is optimized for performance using lazy parsing and caching of components.

## Architecture Overview
- **Type**: Abstract Base Class / Parcelable
- **Package**: `android.net`
- **Subclasses (Private)**:
    -   `StringUri`: Parses a raw string on demand.
    -   `OpaqueUri`: Represents opaque URIs (scheme:ssp#fragment).
    -   `HierarchicalUri`: Represents hierarchical URIs (scheme://auth/path?query#fragment).
-   **Builder**: `Uri.Builder` for constructing URIs.

## Key Design Patterns
-   **Immutable**: All implementations are immutable.
-   **Lazy Parsing (`StringUri`)**: Does not parse components (scheme, authority, path, etc.) until requested.
-   **Caching**: Caches parsed components and string representations to avoid re-parsing. Uses `NotCachedHolder.NOT_CACHED` sentinel to distinguish null results from unparsed states.
-   **Part Abstraction**: Uses `Part` and `PathPart` helper classes (likely internal package-private) to handle encoding/decoding of segments.

## Detailed Functionality

### Components
-   **Scheme**: Protocol (http, file, content).
-   **Scheme Specific Part (SSP)**: Everything after scheme:.
-   **Authority**: UserInfo + Host + Port.
-   **Path**: Path segments.
-   **Query**: Key-value pairs after `?`.
-   **Fragment**: After `#`.

### Decoding/Encoding
-   **`getEncoded*()`**: Returns the raw, percent-encoded string.
-   **`get*()`**: Returns the decoded string (using UTF-8).
-   `UriCodec` is used for decoding.

### Operations
-   `buildUpon()`: Returns a Builder initialized with current URI state.
-   `normalizeScheme()`: Lowercases the scheme.
-   `toSafeString()`: Redacts PII (user info, query params) for logging.

## Data Structures
-   **`PathSegments`**: Wrapper around `String[]` or `ArrayList` for path segments.
-   **`StringUri`**: Stores just the string. Parses offsets for `:` and `#`.
-   **`HierarchicalUri`**: Stores decomposed `Part` objects for authority, path, query, fragment.

## Java-to-C++ Translation Guide

### Optimization Strategy
The key features to replicate are **immutability** and **lazy parsing**.
-   **C++ Class**: `class Uri`.
-   **Subclasses**: `StringUri` (holds `std::string`), `HierarchicalUri` (holds components).
-   **Caching**: Use `mutable` members for cached offsets or parsed strings in `StringUri` to allow caching in `const` methods.

### String Handling
-   Android `Uri` relies heavily on Java String's immutability. In C++, `std::string` is mutable value semantics. `std::shared_ptr<const std::string>` or `std::string_view` (careful with lifetime) might be used to share data.

### Logic
-   **Parsing**: Port `parseAuthority`, `parsePath`, `parseQuery` logic. Note the handling of `//` for authority presence.
-   **Encoding**: Port `encode`/`decode` logic.

### Parcelable
-   Standard serialization: Type ID -> Data.
    -   `NULL_TYPE_ID` (0)
    -   `StringUri` (1): Writes string.
    -   `OpaqueUri` (2): Writes components.
    -   `HierarchicalUri` (3): Writes components.

## Edge Cases
-   **File URIs**: `fromFile()` handles specific escaping.
-   **Parsing Ambiguities**: RFC 2396 vs 3986. Android's `Uri` is mostly 2396 but with some pragmatic looseness.
