# SearchIndexablesProvider - Reverse Engineering Documentation

## Executive Summary
`SearchIndexablesProvider` is the base class for Content Providers that expose data for Settings Search.

## Architecture Overview
- **Inheritance**: `SearchIndexablesProvider` -> `ContentProvider`.

## Detailed Functionality
-   **Querying**: Dispatches queries to abstract methods: `queryXmlResources`, `queryRawData`, `queryNonIndexableKeys`.
-   **Permissions**: Enforces `READ_SEARCH_INDEXABLES` permission.

## API Reference
-   `queryXmlResources`, `queryRawData`, `queryNonIndexableKeys`.

## Java-to-C++ Translation Guide
-   **ContentProvider**: Server-side implementation base.
