# SmartspaceTarget - Reverse Engineering Documentation

## Executive Summary
`SmartspaceTarget` is the core data object representing a single "card" or prediction in the Smartspace UI. It is a highly complex container supporting various features (Weather, Calendar, Flight, etc.), UI templates (Default, Carousel, etc.), and actions.

## Architecture Overview
- **Package**: `android.app.smartspace`
- **Type**: `Parcelable` data class.
- **Role**: The payload delivered from the service to the client.
- **Dependencies**:
  - `SmartspaceAction` (Header, Base, Chips, Grid).
  - `uitemplatedata.BaseTemplateData` (UI Structure).
  - `AppWidgetProviderInfo` / `RemoteViews` / `Uri` (Slice): Alternative rendering payloads.

## Detailed Functionality

### Feature Definition
It defines two key enumerations:
- `FeatureType`: Identifies the content semantics (e.g., `FEATURE_WEATHER`, `FEATURE_FLIGHT`).
- `UiTemplateType`: Identifies the structural layout (e.g., `UI_TEMPLATE_DEFAULT`, `UI_TEMPLATE_CAROUSEL`).

### Rendering Priority
The class documentation defines a strict precedence for rendering properties:
1.  `mRemoteViews` OR `mWidget` (Mutually exclusive, highest priority).
2.  `mSliceUri`.
3.  Data properties (Header, Base Action, Template Data).

### Serialization
**Algorithm**:
- Reads/Writes all fields in a specific order.
- Uses `TypedObject` and `TypedList` for nested Parcelables.
- Handles flags (Boolean) explicitly.

## Data Model

| Field | Type | Description |
|-------|------|-------------|
| `mSmartspaceTargetId` | `String` | Unique ID. |
| `mHeaderAction` | `SmartspaceAction` | Top-level header action. |
| `mBaseAction` | `SmartspaceAction` | Main tap action. |
| `mCreationTimeMillis` | `long` | Creation timestamp. |
| `mExpiryTimeMillis` | `long` | Expiry timestamp. |
| `mScore` | `float` | Relevance score. |
| `mActionChips` | `List<SmartspaceAction>` | Action buttons. |
| `mIconGrid` | `List<SmartspaceAction>` | Grid of icons. |
| `mFeatureType` | `int` | Semantic type. |
| `mSensitive` | `boolean` | Hide on secure lockscreen? |
| `mShouldShowExpanded` | `boolean` | Initial expansion state. |
| `mSourceNotificationKey` | `String` | Linked notification. |
| `mComponentName` | `ComponentName` | Source component. |
| `mUserHandle` | `UserHandle` | User context. |
| `mAssociatedSmartspaceTargetId` | `String` | Linked target ID. |
| `mSliceUri` | `Uri` | Slice content URI. |
| `mWidget` | `AppWidgetProviderInfo` | Widget provider info. |
| `mTemplateData` | `BaseTemplateData` | Structured UI data. |
| `mRemoteViews` | `RemoteViews` | Custom view hierarchy. |

## Java-to-C++ Translation Guide

### Dependencies
- **Polymorphism**: `mTemplateData` is `BaseTemplateData`, but can be a subclass (Carousel, etc.). The C++ Parcel reading logic must handle polymorphic creation based on the data type, or the `BaseTemplateData` parceling logic itself handles it (it does, via `writeParcelable`).
- **Lists**: `List<SmartspaceAction>` maps to `std::vector<SmartspaceAction>`.

### Constants
- The `FeatureType` and `UiTemplateType` integer constants must be replicated in a C++ header file or enum.

### Validation
- The `Builder` enforces non-null checks on `mSmartspaceTargetId`, `mComponentName`, and `mUserHandle`. C++ builder should mirror this.
- The `Builder` enforces mutual exclusivity between Widget and RemoteViews.

## Test Cases & Validation
1.  **Precedence**: Verify documentation logic (Widget > Slice > Data) isn't enforced by code, but by consumer convention.
2.  **Polymorphism**: Ensure `mTemplateData` is parceled/unparceled correctly maintaining its specific subclass type.
