# RestrictionEntry - Reverse Engineering Documentation

## Executive Summary
`RestrictionEntry` represents a single configurable restriction for an application, used in the context of managed profiles or restricted users. It defines the type of restriction (boolean, choice, string, etc.), its key, default value, and current value.

## Architecture Overview
- **Inheritance:** Implements `Parcelable`.
- **Usage:** Used by `RestrictionsManager` and apps to define configuration schemas.

## Types
- `TYPE_NULL` (Hidden)
- `TYPE_BOOLEAN`
- `TYPE_CHOICE` (Single select)
- `TYPE_MULTI_SELECT`
- `TYPE_INTEGER`
- `TYPE_STRING`
- `TYPE_BUNDLE`
- `TYPE_BUNDLE_ARRAY`

## Data Model
- `mType`: `int`.
- `mKey`: `String`.
- `mTitle`, `mDescription`: `String`.
- `mChoiceEntries`, `mChoiceValues`: `String[]`.
- `mCurrentValue`: `String`.
- `mCurrentValues`: `String[]` (For multi-select).
- `mRestrictions`: `RestrictionEntry[]` (For bundle types).

## API Reference
- `public RestrictionEntry(int type, String key)`
- `public void setSelectedString(String selectedString)`
- `public void setSelectedState(boolean state)`
- `public void setAllSelectedStrings(String[] allSelectedStrings)`

## Java-to-C++ Translation Guide
- **Parcelable**: Standard.
- **Polymorphism**: The single class handles multiple types via `mType`. In C++, this might be better modeled as a `std::variant` or a base class with subclasses, though keeping the data-structure approach matches the Binder wire format easier.

## Implementation Risks
- **Data Consistency**: Ensuring `mChoiceEntries` and `mChoiceValues` have the same length.
