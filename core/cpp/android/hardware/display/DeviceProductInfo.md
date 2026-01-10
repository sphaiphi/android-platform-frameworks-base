# DeviceProductInfo - Reverse Engineering Documentation

## Executive Summary
`DeviceProductInfo` encapsulates EDID-like product information about a display (or the device connected to it). It includes Manufacturer ID, Product ID, Name, Manufacture Date, and connection type.

## Architecture Overview
- **Type**: Immutable Data Object / Parcelable
- **Inner Class**: `ManufactureDate` (Week/Year).

## Data Model
- `mName`: String.
- `mManufacturerPnpId`: String (3 char, Plug and Play ID).
- `mProductId`: String.
- `mModelYear`: Integer (nullable).
- `mManufactureDate`: `ManufactureDate` (nullable).
- `mConnectionToSinkType`: Int (Unknown, Built-in, Direct, Transitive).

## Java-to-C++ Translation Guide
- **Optional Integers**: Java uses `Integer` to allow nulls (missing data). C++ should use `std::optional<int32_t>` or a sentinel value (-1).
- **Strings**: `std::string`.
- **Parceling**: `readValue` in Java handles nulls. C++ Parcel API needs to handle "has value" flags or equivalent.

## API Reference
- `getManufacturerPnpId()`
- `getProductId()`
- `getManufactureYear()` / `getManufactureWeek()`
