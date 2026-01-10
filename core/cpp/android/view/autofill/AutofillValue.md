# AutofillValue - Reverse Engineering Documentation

## Executive Summary
Encapsulates a value to be autofilled into a View. Handles different types (Text, Toggle, List, Date).

## Data Model
*   **Type**: `mType` (TEXT, TOGGLE, LIST, DATE).
*   **Value**: `mValue` (Object: CharSequence, Boolean, Integer, Long).

## Java-to-C++ Translation Guide
*   **Variant**: Similar to `std::variant`.
*   **Parcelable**: Serialization.
