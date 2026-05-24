# ContextParams - Reverse Engineering Documentation

## Executive Summary
`ContextParams` encapsulates parameters for creating a new `Context`. It allows customizing behavior like permission attribution (attribution tag, source) and renounced permissions.

## Architecture Overview
- **Pattern:** Immutable object with Builder.
- **Usage:** Passed to `Context.createContext(ContextParams)`.

## Data Model
-   `mAttributionTag`: `String`.
-   `mNext`: `AttributionSource` (The next attribution source in the chain).
-   `mRenouncedPermissions`: `Set<String>`.
-   `mShouldRegisterAttributionSource`: `boolean`.

## API Reference
-   `public @Nullable String getAttributionTag()`
-   `public @NonNull Set<String> getRenouncedPermissions()`
-   `public @Nullable AttributionSource getNextAttributionSource()`

## Java-to-C++ Translation Guide
-   **Builder**: Standard builder pattern.
-   **Sets**: `std::set` or `std::unordered_set`.

## Implementation Risks
-   None.
