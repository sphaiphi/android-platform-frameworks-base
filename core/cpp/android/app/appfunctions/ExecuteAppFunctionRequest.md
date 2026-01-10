# ExecuteAppFunctionRequest - Reverse Engineering Documentation

## Executive Summary
Represents a request from a client app to execute a specific function. Contains target package, function ID, parameters, and extras.

## Architecture Overview
-   **Type**: Parcelable Data Class.
-   **Pattern**: Builder Pattern.

## Data Model
-   `mTargetPackageName`: `String`
-   `mFunctionIdentifier`: `String`
-   `mParameters`: `GenericDocumentWrapper` (Lazy wrapper around `GenericDocument`)
-   `mExtras`: `Bundle`

## API Reference
-   Getters.
-   `Builder` class.
-   `getRequestDataSize()`: Helper for metrics.

## Java-to-C++ Translation Guide
-   **GenericDocument**: This is the AppSearch document type. C++ needs to handle the `GenericDocumentWrapper` serialization which involves blob handling.

## Test Cases & Validation
-   **Parameters**: Verify `GenericDocument` is correctly wrapped/unwrapped.

## Implementation Risks
-   **Large Data**: `GenericDocumentWrapper` handles large blobs; logic must be robust.
