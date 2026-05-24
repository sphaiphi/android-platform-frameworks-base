# AppFunctionManagerHelper - Reverse Engineering Documentation

## Executive Summary
Helper class providing logic for interacting with `AppSearchManager` to query App Function metadata. Specifically handles the `isAppFunctionEnabled` logic by querying joined static and runtime metadata from AppSearch.

## Architecture Overview
-   **Role**: Utility / Logic implementation.
-   **Dependencies**: `AppSearchManager`, `GlobalSearchSession`, `SearchSpec`, `JoinSpec`.

## Detailed Functionality

### `isAppFunctionEnabled`
**Algorithm**:
1.  **Session Creation**: Creates a `GlobalSearchSession` asynchronously.
2.  **Search**: Calls `searchJoinedStaticWithRuntimeAppFunctions`.
    -   **Join Spec**: Joins Runtime metadata (child) on Static metadata (parent) using `appFunctionStaticMetadataQualifiedId`.
    -   **Query**: Filters by `functionId`.
    -   **Projection**: Only requests `enabledByDefault`.
3.  **Result Processing**:
    -   Iterates results.
    -   Calls `getEffectiveEnabledStateFromSearchResults`.
4.  **Effective State Logic**:
    -   If no results: Throws `AppFunctionNotFoundException`.
    -   If runtime metadata exists and `enabled` != DEFAULT (0): Return runtime value (1=Enabled, 2=Disabled).
    -   Else: Return static metadata `enabledByDefault`.

### Helper Methods
-   `searchJoinedStaticWithRuntimeAppFunctions`: Builds complex `SearchSpec` with Join.
-   `getAppFunctionRuntimeMetadataSearchSpecByPackageName`: Scopes search to `android` package (indexer) and package specific schema.
-   `failedResultToException`: Maps AppSearch error codes to Exceptions.

## Data Model
Uses constants from `AppFunctionRuntimeMetadata` and `AppFunctionStaticMetadataHelper`.

## API Reference
-   `static void isAppFunctionEnabled(...)`

## Java-to-C++ Translation Guide
-   **AppSearch**: This logic heavily relies on AppSearch Java APIs. If C++ AppSearch APIs exist, translate directly. If not, this logic might need to stay in Java or go via JNI.
-   **Async flow**: The nested callback structure (Session -> Search -> Page) needs careful translation to C++ async patterns (e.g. Futures, Coroutines, or nested callbacks).

## Test Cases & Validation
-   **Not Found**: Search returns empty -> Expect Error.
-   **Runtime Override**: Runtime enabled=1, Static enabled=false -> Expect True.
-   **Default**: Runtime enabled=0, Static enabled=true -> Expect True.

## Implementation Risks
-   **AppSearch Query Syntax**: Ensure exact string formatting for filters (`functionId:"value"`).
-   **Schema Names**: Must match the schema generation logic exactly.

## Questions for C++ Team
-   Is AppSearch accessible from the C++ layer where this will run?
