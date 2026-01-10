# Dataset - Reverse Engineering Documentation

## Executive Summary
`Dataset` represents a set of fields (views) and their corresponding values to be autofilled. It allows filling multiple fields simultaneously (e.g., username and password) when the user selects a single option.

## Data Model

### Core Components
*   **Field IDs**: `ArrayList<AutofillId>` - IDs of views to fill.
*   **Field Values**: `ArrayList<AutofillValue>` - Values to fill into those views.
*   **Presentations**: `ArrayList<RemoteViews>` - UI to show for each field (dropdown).
*   **Inline Presentations**: `ArrayList<InlinePresentation>` - UI for inline suggestions (keyboard).
*   **Authentication**: `IntentSender` - If set, the dataset is "locked" until the user authenticates (e.g., providing a fingerprint for credit card info).
*   **Filter**: `ArrayList<DatasetFieldFilter>` - Regex to filter when this dataset is shown based on user input.

### Key Concepts
*   **Presentations**: Can have a global presentation (for the whole dataset) or per-field presentations.
*   **Eligible Reason**: Why this dataset was picked (Provider vs PCC - Platform Content Capture).

## API Reference

### Builder (`Dataset.Builder`)
*   **`setField(AutofillId id, Field field)`**: The main way to add data. `Field` wraps value, presentation, and filter.
*   **`setAuthentication(IntentSender)`**: Sets the auth flow.
*   **`setId(String id)`**: Sets a tracking ID.
*   **`setContent(AutofillId id, ClipData content)`**: For rich content (images) support (Augmented Autofill).

### Getters
*   `getFieldIds()`, `getFieldValues()`, `getFieldPresentation(int index)`, `getAuthentication()`, `getId()`.

## Java-to-C++ Translation Guide

### Parcelable
*   **Java**: Custom `writeToParcel`/`createFromParcel` logic. Complex serialization due to multiple parallel lists (Ids, Values, Presentations).
*   **C++**: `android::Parcelable`. The serialization format MUST match exactly.
    *   Writes: Presentation(s), InlinePresentation(s), FieldIds (TypedList), FieldValues (TypedList), etc.

### Builder Pattern
*   **Java**: `Dataset.Builder`.
*   **C++**: Should implement a similar Builder to construct the immutable `Dataset` object.

### Dependencies
*   `AutofillId`, `AutofillValue`, `RemoteViews`, `InlinePresentation`.

## Implementation Notes
*   **Validation**: Builder enforces that at least one field or value is set.
*   **Immutability**: Once built, the `Dataset` is immutable.
