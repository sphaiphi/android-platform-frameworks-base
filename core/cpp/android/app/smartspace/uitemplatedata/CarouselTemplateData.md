# CarouselTemplateData - Reverse Engineering Documentation

## Executive Summary
`CarouselTemplateData` extends `BaseTemplateData` to support a horizontally scrollable list of items (carousel) embedded within the standard Smartspace card layout.

## Architecture Overview
- **Package**: `android.app.smartspace.uitemplatedata`
- **Parent**: `BaseTemplateData`.
- **Type**: `Parcelable`.
- **Template Type**: `UI_TEMPLATE_CAROUSEL`.

## Detailed Functionality

### Data Extension
Adds two fields to the base layout:
- `mCarouselItems`: A list of `CarouselItem` objects.
- `mCarouselAction`: A tap action for the entire carousel area.

### Serialization
**Algorithm**:
1.  Calls `super.writeToParcel`.
2.  Writes `mCarouselItems` (TypedList).
3.  Writes `mCarouselAction` (Parcelable).

## Data Model

| Field | Type | Description |
|-------|------|-------------|
| `mCarouselItems` | `List<CarouselItem>` | The scrollable content. |
| `mCarouselAction` | `TapAction` | Fallback action. |

## Inner Class: CarouselItem
**Purpose**: Represents a single column/card in the carousel.
**Layout**:
- Upper Text
- Image
- Lower Text
- Tap Action

## Java-to-C++ Translation Guide
- **Inheritance**: C++ class should inherit from `BaseTemplateData`.
- **Lists**: `std::vector<CarouselItem>`.

## Test Cases & Validation
1.  **Empty List**: Builder throws `IllegalStateException` if the list is empty. C++ constructor/builder should enforce this.
