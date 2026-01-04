# FieldClassification - Reverse Engineering Documentation

## Executive Summary
`FieldClassification` is a data class (Parcelable) representing the classification result for a specific field (identified by `AutofillId`). It contains a set of "hints" (Strings) indicating what the field is believed to be (e.g., "username", "creditCardNumber").

## Data Model

### Fields
*   `mAutofillId`: `AutofillId` (NonNull) - The unique ID of the field.
*   `mHints`: `Set<String>` (NonNull) - The detected types/hints.
*   `mGroupHints`: `Set<String>` (NonNull) - Higher-level groupings of hints (e.g., "postalAddress" for "streetAddress").

## API Reference

### Getters
*   `AutofillId getAutofillId()`
*   `Set<String> getHints()`
*   `Set<String> getGroupHints()`

### Construction
*   Constructor taking `AutofillId`, `Set<String>` hints, and optional `Set<String>` groupHints.

## Java-to-C++ Translation Guide

### Parcelable
*   **Java**: Implements `Parcelable` with helper methods `parcelHints` / `unparcelHints` because `Parcel` doesn't natively support `Set<String>` directly (it usually does Lists).
*   **C++**: `android::Parcelable`. Use `writeStringVector` or similar for the sets (converting to/from `std::vector` or `std::set`).

### Dependencies
*   `AutofillId` (from `android.view.autofill`).

## Implementation Notes
*   **Immutability**: The class is immutable.
*   **Sets**: Java uses `ArraySet`. C++ can use `std::set` or `std::vector` if order doesn't matter (though `ArraySet` preserves order usually, `Set` contract doesn't guarantee it, but `ArraySet` is often used for small sets for performance). `FieldClassificationService` creates them.
