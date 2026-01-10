# CombinedCardsTemplateData - Reverse Engineering Documentation

## Executive Summary
`CombinedCardsTemplateData` allows multiple distinct card templates to be grouped together. Currently, it supports combining a "Sub-List" card with a "Sub-Card" card, but the structure is generic (`List<BaseTemplateData>`).

## Architecture Overview
- **Package**: `android.app.smartspace.uitemplatedata`
- **Parent**: `BaseTemplateData`.
- **Type**: `Parcelable`.
- **Template Type**: `UI_TEMPLATE_COMBINED_CARDS`.

## Detailed Functionality

### Data Extension
- `mCombinedCardDataList`: A list of `BaseTemplateData` objects.

### Serialization
- Calls `super.writeToParcel`.
- Writes `mCombinedCardDataList`.

## Data Model

| Field | Type | Description |
|-------|------|-------------|
| `mCombinedCardDataList` | `List<BaseTemplateData>` | Sub-cards. |

## Java-to-C++ Translation Guide
- **Recursive Structure**: This class contains a list of its own base class. The C++ parser must handle this recursive definition (likely via pointers/smart pointers to avoid infinite size issues if value semantics were used, though `std::vector` handles size).
- **Polymorphism**: The list contains `BaseTemplateData`, but the elements are likely specific subclasses (SubList, SubCard). The unparcelling logic for the list elements needs to be polymorphic.

## Test Cases & Validation
1.  **Polymorphism**: Verify that the list can contain different subtypes of `BaseTemplateData`.
