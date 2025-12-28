# AppFunctionStaticMetadataHelper - Reverse Engineering Documentation

## Executive Summary
Helper class defining constants and ID generation logic for **Static** App Function metadata (indexed from Manifest/XML).

## Architecture Overview
-   **Role**: Constants container / Utility.

## Detailed Functionality
-   **Schema Constants**: `AppFunctionStaticMetadata`, properties for `enabledByDefault`, `functionId`, etc.
-   **ID Helpers**: `getStaticSchemaNameForPackage`, `getDocumentIdForAppFunction`, `getStaticMetadataQualifiedId`.

## Data Model
-   `APP_FUNCTION_STATIC_METADATA_DB` = "apps-db"
-   `APP_FUNCTION_STATIC_NAMESPACE` = "app_functions"

## Java-to-C++ Translation Guide
-   **Constants**: replicate exact strings in C++ header.

## Test Cases & Validation
-   **Qualified ID**: Verify format matches `DocumentIdUtil.createQualifiedId`.

## Implementation Risks
-   **Consistency**: Must match the values used by the `AppFunctionIndexer` (system service).
