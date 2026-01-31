# android.net.Uri - Reverse Engineering Documentation

## Executive Summary
`Uri` is an immutable reference to a Universal Resource Identifier. It supports both hierarchical (e.g., `http://...`) and opaque (e.g., `mailto:...`) URIs.

## Architecture Overview
- **Structure**: Abstract base class with specialized internal implementations (`StringUri`, `OpaqueUri`, `HierarchicalUri`).
- **Immutability**: Guaranteed immutable. Caching is used for performance.

## Detailed Functionality

### Components
- **Scheme**: Protocol (e.g., `http`).
- **Scheme-Specific Part (SSP)**: Everything after the scheme.
- **Authority**: `[userinfo@]host[:port]`.
- **Path**: Path segments.
- **Query**: Key-value pairs.
- **Fragment**: Resource pointer.

### Parsing
- `parse(String)`: Main entry point. Creates a `StringUri`.
- `fromFile(File)`: Creates a `HierarchicalUri`.

### Parceling (Wire Format)
`Uri` uses a custom parceling scheme with a type ID discriminator:
1. `int typeID`:
    - `0`: NULL
    - `1`: `StringUri` (Writes the full URI string)
    - `2`: `OpaqueUri`
    - `3`: `HierarchicalUri`
2. Data follows based on `typeID`. `StringUri` simply writes/reads a string.

## Data Model
- `scheme`: String
- `authority`: String
- `path`: String
- `query`: String
- `fragment`: String

## API Reference
- `getScheme()`, `getAuthority()`, `getPath()`, `getQuery()`, `getFragment()`
- `isHierarchical()`, `isOpaque()`, `isRelative()`, `isAbsolute()`
- `buildUpon()`: Returns a `Builder` for modification.

## Java-to-C++ Translation Guide
- **Implementations**: A single robust C++ class might be simpler than mirroring the Java hierarchy, provided it handles both opaque and hierarchical cases.
- **Parceling Compatibility**: MUST support the `typeID` discriminator and match the `StringUri` (ID 1) format at a minimum, as most URIs are parceled this way.
- **Error Handling**: Use `std::expected` for parsing failures.

## Test Cases & Validation
- Parsing various URI strings.
- Accessing individual components.
- Building URIs with `Builder`.
- Parcel round-trip with discriminator.

## Implementation Risks
- Performance: URI parsing can be slow. Use efficient string views and caching.
- RFC 2396 Compliance: Ensure parsing rules match Java's interpretation.
- Encoding/Decoding: Correctly handle percent-encoding.