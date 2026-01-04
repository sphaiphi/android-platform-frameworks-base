# Adapter - Reverse Engineering Documentation

## Executive Summary
`Adapter` is the root interface for all adapters in the Android widget framework. It acts as a bridge between an `AdapterView` (like ListView, GridView) and the underlying data source.

## Architecture Overview
*   **Type**: Interface.
*   **Hierarchy**: Root. Extended by `ListAdapter`, `SpinnerAdapter`.

## API Contract

### 1. Data Access
*   `getCount()`: Total number of items.
*   `getItem(int position)`: Data object at position.
*   `getItemId(int position)`: Unique ID for the item.

### 2. View Generation
*   `getView(int position, View convertView, ViewGroup parent)`: Returns the visual representation of the item.
    *   **`convertView`**: The recycling mechanism. If non-null, the implementation should update this view instead of inflating a new one.

### 3. View Types
*   `getItemViewType(int position)`: Supports heterogeneous lists (different layouts for different rows).
*   `getViewTypeCount()`: Total number of view types.

### 4. Identification
*   `hasStableIds()`: optimization hint.

### 5. Observation
*   `registerDataSetObserver(...)` / `unregister...`: Notification mechanism for data changes.

## Java-to-C++ Translation Guide
*   **Virtual Base Class**: In C++, this should be an abstract base class (interface).
*   **Memory Management**: `getItem` usually returns `Object` in Java. In C++, this might be `void*`, `std::any`, or a templated type `T`.
*   **View Ownership**: The `getView` contract implies shared ownership or view pooling. C++ UI frameworks often handle view lifecycle differently; care is needed regarding who owns the `View` pointer returned.
