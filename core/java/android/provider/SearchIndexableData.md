# SearchIndexableData - Reverse Engineering Documentation

## Executive Summary
`SearchIndexableData` is a base class for data types that can be indexed for device search (Settings search).

## Architecture Overview
- **Type**: Abstract Data Class.
- **Subclasses**: `SearchIndexableResource`, `RawData`.

## Data Model
-   `context`, `locale`, `enabled`, `rank`, `key`.
-   `className`, `packageName`, `iconResId`.
-   `intentAction`, `intentTargetPackage`, `intentTargetClass`.

## Java-to-C++ Translation Guide
-   **Struct**: Base struct for search data.
