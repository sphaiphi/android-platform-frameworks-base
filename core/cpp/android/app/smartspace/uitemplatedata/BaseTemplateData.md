# BaseTemplateData - Reverse Engineering Documentation

## Executive Summary
`BaseTemplateData` is the foundational data structure for all Smartspace UI templates. It defines the common layout elements (primary item, subtitle, supplemental info) and behavior shared across different visual representations of a Smartspace card. It serves as both a concrete implementation for the default template and a base class for specialized templates (Carousel, HeadToHead, etc.).

## Architecture Overview
- **Package**: `android.app.smartspace.uitemplatedata`
- **Type**: `Parcelable` Base Class.
- **Role**: Defines the schema for a standard Smartspace card layout.
- **Subclasses**: `CarouselTemplateData`, `HeadToHeadTemplateData`, `CombinedCardsTemplateData`, `SubCardTemplateData`, `SubImageTemplateData`, `SubListTemplateData`.
- **Inner Classes**: `SubItemInfo` (Renderable unit), `SubItemLoggingInfo` (Analytics).

## Detailed Functionality

### Template Identification
**Field**: `mTemplateType`
**Purpose**: Discriminator for polymorphic parsing. Identifies if the object is a `BaseTemplateData` or a specialized subclass.
**Values**: Defined in `SmartspaceTarget.UiTemplateType` (e.g., `UI_TEMPLATE_DEFAULT`, `UI_TEMPLATE_CAROUSEL`).

### Layout Model
The base template defines a specific row-based layout:
1.  **Row 1**: `mPrimaryItem` (Title/Icon).
2.  **Row 2**: `mSubtitleItem` + `mSubtitleSupplementalItem`.
3.  **Row 3**: `mSupplementalLineItem` OR `mSupplementalAlarmItem`.

**Attributes**:
- `mLayoutWeight`: hints at spatial priority (0 by default).

### Serialization
**Algorithm**:
- Writes template type (Int).
- Writes all SubItemInfo objects (Parcelable).
- Writes layout weight (Int).
- **Note**: Subclasses call `super.writeToParcel` first, ensuring the base data is always at the head of the parcel.

## Data Model

| Field | Type | Description |
|-------|------|-------------|
| `mTemplateType` | `int` | Type constant. |
| `mPrimaryItem` | `SubItemInfo` | Title row data. |
| `mSubtitleItem` | `SubItemInfo` | Subtitle row start. |
| `mSubtitleSupplementalItem` | `SubItemInfo` | Subtitle row end. |
| `mSupplementalLineItem` | `SubItemInfo` | 3rd row generic. |
| `mSupplementalAlarmItem` | `SubItemInfo` | 3rd row alarm specific. |
| `mLayoutWeight` | `int` | Layout priority. |

## Inner Class: SubItemInfo
**Purpose**: A reusable atom for UI elements.
**Components**:
- `mText`: Text content.
- `mIcon`: Drawable icon.
- `mTapAction`: Interaction handler.
- `mLoggingInfo`: Analytics data.

## Inner Class: SubItemLoggingInfo
**Purpose**: Analytics metadata.
**Components**:
- `mInstanceId`: Unique ID.
- `mFeatureType`: Semantic type.
- `mPackageName`: Data source.

## Java-to-C++ Translation Guide

### Polymorphism
- **Java**: Uses `Parcelable` inheritance. `SmartspaceTarget` reads this field.
- **C++**: The C++ reader for `SmartspaceTarget` must read the `int mTemplateType` first, then decide which C++ class to instantiate (`BaseTemplateData` vs `CarouselTemplateData`) before reading the rest of the stream.

### Data Structures
- `SubItemInfo` maps to a C++ struct/class.
- `SubItemLoggingInfo` maps to a C++ struct/class.

### Builder Pattern
- The Java Builder is standard. C++ should provide a similar fluent interface or struct-based initialization.

## Test Cases & Validation
1.  **Polymorphism**: Ensure that a `CarouselTemplateData` written to a parcel can be identified correctly by reading the first integer.
2.  **Nullability**: All `SubItemInfo` fields are nullable.
