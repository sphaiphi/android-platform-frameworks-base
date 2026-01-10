# BaseColumns - Reverse Engineering Documentation

## Executive Summary
`BaseColumns` is a standard interface for database columns, defining the `_ID` and `_COUNT` columns common to many Android Content Providers.

## Architecture Overview
- **Type**: Interface (Constants).
- **Role**: Defines standard DB columns.

## Data Model
-   `_ID`: "_id" (INTEGER/long) - Unique row ID.
-   `_COUNT`: "_count" (INTEGER) - Row count.

## Java-to-C++ Translation Guide
-   **Constants**: Map to C++ string constants.
