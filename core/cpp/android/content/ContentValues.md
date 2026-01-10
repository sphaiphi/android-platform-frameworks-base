# ContentValues - Reverse Engineering Documentation

## Executive Summary
`ContentValues` is a map-like class used to store a set of values (key-value pairs) that the `ContentResolver` can process. It handles various primitive types and ensures they are parcelable.

## Architecture Overview
- **Inheritance:** Implements `Parcelable`.
- **Underlying Data:** `ArrayMap<String, Object>`.

## Detailed Functionality
- **Put methods**: `put(String key, String value)`, `put(String key, Integer value)`, etc. Stores values in the map.
- **Get methods**: `getAsString`, `getAsInteger`, etc. handling type casting and string conversion.

## Data Model
- `mMap`: `ArrayMap<String, Object>`.

## API Reference
- `public void put(String key, String value)`
- `public String getAsString(String key)`
- `public int size()`

## Java-to-C++ Translation Guide
- **Variant**: The values are effectively a `Variant` type (String, Number, Byte array, Null). C++ `std::variant` or a custom `Value` class is needed.
- **Map**: `std::map<std::string, Variant>`.
- **Parcelable**: Needs to match the Parcel format (writing size then key-values).

## Implementation Risks
- **Type Safety**: The `getAs...` methods do loose conversion (e.g. String to Long). C++ implementation should replicate this behavior or define strict rules.
