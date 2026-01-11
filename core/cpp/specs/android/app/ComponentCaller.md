# ComponentCaller - Reverse Engineering Documentation

## Executive Summary
`ComponentCaller` wraps the identity (UID, Package Name) of the app that launched a component (Activity). It provides a secure way to access this information and check permissions (content URIs) granted by the caller.

## Architecture Overview
*   **Type**: Immutable Wrapper.
*   **Dependencies**: `ActivityClient`.

## Detailed Functionality
*   **Identity**: `getUid()`, `getPackage()`. Retrieves from `ActivityClient` using tokens.
*   **Permission Check**: `checkContentUriPermission(Uri, int)`. Checks if the caller has access to a URI.

## Java-to-C++ Translation Guide
*   Wrapper around Binder/Service calls.

## Implementation Risks
*   **Token Validity**: Relies on valid `ActivityToken` and `CallerToken`.
