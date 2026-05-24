# SaveInfo - Reverse Engineering Documentation

## Executive Summary
`SaveInfo` describes *what* data can be saved and *when* to trigger the save UI. It is part of the `FillResponse`.

## Data Model

### Core Fields
*   `mType`: `int` - Bitmask of data types (e.g., `SAVE_DATA_TYPE_PASSWORD`).
*   `mRequiredIds`: `AutofillId[]` - Fields that *must* change/be non-empty to trigger save.
*   `mOptionalIds`: `AutofillId[]` - Extra fields to save if available.
*   `mDescription`: `CharSequence` - Subtitle for the UI.
*   `mFlags`: `int` - Behavior flags (e.g., `FLAG_SAVE_ON_ALL_VIEWS_INVISIBLE`).
*   `mCustomDescription`: `CustomDescription` - Complex UI for the save dialog.
*   `mValidator`: `InternalValidator` - Condition to validate before showing save UI.
*   `mSanitizers`: `InternalSanitizer[]` - Logic to clean data (e.g., remove spaces from credit card) before saving.
*   `mTriggerId`: `AutofillId` - Explicit view that triggers save when clicked.

### Constants
*   **Types**: `SAVE_DATA_TYPE_GENERIC`, `PASSWORD`, `ADDRESS`, `CREDIT_CARD`, etc.
*   **Flags**: `FLAG_SAVE_ON_ALL_VIEWS_INVISIBLE`, `FLAG_DONT_SAVE_ON_FINISH`, `FLAG_DELAY_SAVE`.

## API Reference

### Builder (`SaveInfo.Builder`)
*   **Constructor**: Takes `type` and `requiredIds`.
*   **`setOptionalIds`**: Adds optional fields.
*   **`setFlags`**: Configures triggers.
*   **`setDescription`** / **`setCustomDescription`**: UI customization.
*   **`setValidator`**: Adds validation logic (Regex, Luhn).
*   **`addSanitizer`**: Adds sanitization logic.
*   **`setTriggerId`**: Sets explicit trigger.

## Java-to-C++ Translation Guide

### Parcelable
*   **Java**: Custom serialization.
    *   Writes validators, sanitizers (Map of Sanitizer -> Ids), custom descriptions.
*   **C++**: `android::Parcelable`.
    *   Need to handle polymorphic `InternalValidator` and `InternalSanitizer` writing.

### Dependencies
*   `AutofillId`, `CustomDescription`, `InternalValidator`, `InternalSanitizer`.

## Implementation Notes
*   **Logic**: The system uses `RequiredIds` to determine "dirty" state. If a required ID's value hasn't changed from the initial value or the filled value, save isn't triggered.
