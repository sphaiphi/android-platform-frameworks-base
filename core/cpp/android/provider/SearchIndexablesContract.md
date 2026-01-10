# SearchIndexablesContract - Reverse Engineering Documentation

## Executive Summary
`SearchIndexablesContract` defines the contract for providers that supply indexable data for Settings Search.

## Architecture Overview
- **Authority**: Application-specific (defined by `SEARCH_INDEXABLES_PROVIDER` action).
- **Paths**: `indexables_xml_res`, `indexables_raw`, `non_indexables_key`, `site_map_pairs`, `slice_uri_pairs`.

## Detailed Functionality
-   **Columns**: Defines column schemas for XML resources, Raw Data, and Non-indexable keys.

## Java-to-C++ Translation Guide
-   **Schema**: Database schemas.
