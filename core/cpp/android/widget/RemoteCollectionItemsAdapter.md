# RemoteCollectionItemsAdapter - Reverse Engineering Documentation

## Executive Summary
`RemoteCollectionItemsAdapter` is an adapter backed by `RemoteCollectionItems` (a data packet from `RemoteViews`). It allows a `ListView` in the host process to display items provided by a remote process without a live Binder connection for every item.

## Architecture Overview
*   **Inheritance**: `BaseAdapter` -> `RemoteCollectionItemsAdapter`.
*   **Data**: `RemoteCollectionItems`.

## Detailed Functionality
*   **Mapping**: Maps layout IDs to Item View Types (`mLayoutIdToViewType`) to support recycling.
*   **View Generation**: Inflates `RemoteViews` into `AppWidgetHostView`.

## Java-to-C++ Translation Guide
*   **Serialization**: Needs to handle the serialized `RemoteCollectionItems`.

## Implementation Risks
*   **View Types**: If the remote data has more view types than the adapter was initialized with, it throws an exception.
