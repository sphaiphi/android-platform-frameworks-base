# ExecuteAppFunctionAidlRequest - Reverse Engineering Documentation

## Executive Summary
Internal Parcelable class used to pass execution requests across AIDL (Binder). It wraps the client request and adds caller identity/metadata.

## Architecture Overview
-   **Type**: Parcelable Data Class.
-   **Role**: DTO for Binder IPC.

## Data Model
-   `mClientRequest`: `ExecuteAppFunctionRequest`
-   `mUserHandle`: `UserHandle` (Target user)
-   `mCallingPackage`: `String`
-   `mRequestTime`: `long`

## API Reference
-   Getters for all fields.
-   Parcelable implementation.

## Java-to-C++ Translation Guide
-   **Parcelable**: Implement `writeToParcel`/`readFromParcel`.
-   **Composition**: Embeds `ExecuteAppFunctionRequest` parceling logic.

## Test Cases & Validation
-   **Serialization**: Round-trip test.

## Implementation Risks
-   **UserHandle**: Ensure correct serialization of `UserHandle` in C++.
