# AppFunctionRuntimeMetadata - Reverse Engineering Documentation

## Executive Summary
Defines the schema and data model for **Runtime** metadata of App Functions stored in AppSearch. This includes the enabled state of a function. It extends `GenericDocument`.

## Architecture Overview
-   **Inheritance**: `GenericDocument` (AppSearch).
-   **Role**: Data Object / Schema Definition.

## Detailed Functionality

### Schema Definition
-   **Schema Type**: `AppFunctionRuntimeMetadata-[packageName]`.
-   **Properties**:
    -   `functionId` (String, Exact match)
    -   `packageName` (String, Exact match)
    -   `enabled` (Long, Range index)
    -   `appFunctionStaticMetadataQualifiedId` (String, Joinable)

### ID Generation
-   **Document ID**: `packageName + "/" + functionId`
-   **Qualified ID**: `android$apps-db/app_functions/packageName/functionId` (constructed helper).

## Data Model
-   `PROPERTY_FUNCTION_ID` = "functionId"
-   `PROPERTY_PACKAGE_NAME` = "packageName"
-   `PROPERTY_ENABLED` = "enabled"
-   `PROPERTY_APP_FUNCTION_STATIC_METADATA_QUALIFIED_ID` = "appFunctionStaticMetadataQualifiedId"

## API Reference
-   `createAppFunctionRuntimeSchema(packageName)`
-   `Builder` class for creating documents.
-   Getters for properties.

## Java-to-C++ Translation Guide
-   **AppSearch Schema**: Map to C++ AppSearch schema builder if available.
-   **String formatting**: Use `std::string` concatenation or formatting.

## Test Cases & Validation
-   **ID Consistency**: Verify `getDocumentIdForAppFunction` matches what is used in `AppFunctionStaticMetadataHelper`.

## Implementation Risks
-   **Magic Strings**: Schema type separators and property names must be bit-exact matches with the Indexer logic.
