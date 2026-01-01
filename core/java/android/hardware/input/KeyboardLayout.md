# KeyboardLayout - Reverse Engineering Documentation

## Executive Summary
`KeyboardLayout` describes a software keyboard layout configuration, including its name, locale, and physical layout type (e.g., QWERTY, AZERTY).

## Architecture Overview
- **Parcelable**: Transmissible.
- **Comparable**: Implements `Comparable<KeyboardLayout>` for sorting (Priority > LayoutType > Label > Collection).

## Detailed Functionality

### Metadata
- `descriptor`: Unique ID.
- `label`: Display name.
- `collection`: Grouping (e.g., receiver name).
- `priority`: Sorting order.
- `locales`: Supported `LocaleList`.
- `layoutType`: Enum (QWERTY, AZERTY, etc.).
- `vendorId`/`productId`: Hardware restrictions (-1 if generic).

### Physical Layout Helpers
- `isAnsiLayout()`: Checks if US locale + not Extended.
- `isJisLayout()`: Checks if JP locale.

## Data Model
- `enum LayoutType`: Maps integer values to string names (e.g., 1 -> "qwerty").

## API Reference
- Getters for all fields.
- `compareTo` logic.

## Java-to-C++ Translation Guide
- **Locales**: `std::string` (comma-separated BCP-47 tags).
- **Sorting**: Implement `operator<`.

## Implementation Risks
- Locale handling and parsing in C++ vs Java `LocaleList`.
