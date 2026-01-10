# AppJankStats - Reverse Engineering Documentation

## Executive Summary
`AppJankStats` is an immutable data transfer object (DTO) responsible for encapsulating detailed jank statistics for a specific UI widget. It correlates "janky frames" with total rendered frames while a widget is in a specific state (e.g., scrolling, animating). This class serves as the standardized payload for reporting performance metrics from library widgets to the system.

## Architecture Overview
- **Type**: Immutable DTO / Value Object.
- **Package**: `android.app.jank`
- **Role**: Carrier for aggregated jank metrics.
- **Relationships**:
    - Used by `JankTracker` (indirectly via merging) and `JankDataProcessor`.
    - Contains a `RelativeFrameTimeHistogram` to store frame timing distribution.

## Detailed Functionality

### Core Data Encapsulation
**Purpose**: Stores a snapshot of performance metrics for a specific widget context.
**Fields**:
- `mUid` (int): Application UID.
- `mWidgetId` (String): Unique identifier for the UI element.
- `mWidgetCategory` (String): Broad functional category (e.g., "scroll", "animation").
- `mWidgetState` (String): Specific interaction state (e.g., "scrolling", "dragging").
- `mTotalFrames` (long): Total frames rendered during the tracked session.
- `mJankyFrames` (long): Subset of frames considered janky.
- `mRelativeFrameTimeHistogram` (RelativeFrameTimeHistogram): Distribution of frame rendering times relative to the deadline.
- `mNavigationComponent` (String): Optional association with a navigation destination.

### String Definitions (Constants)
**Purpose**: Defines standardized vocabulary for categories and states to ensure consistency across the system.
**Java-Specific Notes**: Uses `@StringDef` annotation for compile-time validation of string constants, which effectively acts like a String-based Enum in C++.
**Categories**: `unspecified`, `scroll`, `animation`, `media`, `navigation`, `keyboard`, `other`.
**States**: `unspecified`, `none`, `scrolling`, `flinging`, `swiping`, `dragging`, `zooming`, `animating`, `playback`, `tapping`, `predictive_back`.

## Data Model

### Class: AppJankStats
| Field | Type | Description |
|-------|------|-------------|
| `mUid` | `int32_t` | The UID of the application. |
| `mWidgetId` | `std::string` | Identifier for the widget. |
| `mNavigationComponent` | `std::string` | (Optional) Navigation target identifier. |
| `mWidgetCategory` | `std::string` | Category constant. Default: "unspecified". |
| `mWidgetState` | `std::string` | State constant. Default: "unspecified". |
| `mTotalFrames` | `int64_t` | Total frames rendered. |
| `mJankyFrames` | `int64_t` | Count of janky frames. |
| `mRelativeFrameTimeHistogram` | `Object` | Reference to histogram object. |

## API Reference

### Constructor
```java
public AppJankStats(int appUid, String widgetId, String navigationComponent, 
                    String widgetCategory, String widgetState, 
                    long totalFrames, long jankyFrames, 
                    RelativeFrameTimeHistogram relativeFrameTimeHistogram)
```
- **Parameters**: Fully initializes all fields.
- **Null Handling**:
    - `widgetCategory` defaults to `WIDGET_CATEGORY_UNSPECIFIED` if null.
    - `widgetState` defaults to `WIDGET_STATE_UNSPECIFIED` if null.
    - `widgetId` and `relativeFrameTimeHistogram` must be non-null.

### Getters
- `getUid()`: Returns `int`.
- `getWidgetId()`: Returns `String`.
- `getWidgetCategory()`: Returns `String`.
- `getWidgetState()`: Returns `String`.
- `getJankyFrameCount()`: Returns `long`.
- `getTotalFrameCount()`: Returns `long`.
- `getRelativeFrameTimeHistogram()`: Returns `RelativeFrameTimeHistogram`.
- `getNavigationComponent()`: Returns `String` (nullable).

## Java-to-C++ Translation Guide

### String Defs
Java uses String constants with `@StringDef`.
- **C++ Recommendation**: Use `enum class` or `static constexpr char*` constants. Given the logging / serialization nature, string constants might be preserved, but an enum mapping is preferred for internal logic.

### Immutability
The class is effectively immutable after construction (no setters).
- **C++ Recommendation**: Mark member variables as `const` or provide only `const` accessors. Delete copy constructors if unique ownership is intended, though this looks like a value type that should be copyable/movable.

### Nullability
- **Java**: `String` can be null.
- **C++**: Use `std::optional<std::string>` for nullable fields like `mNavigationComponent`, or an empty string convention if appropriate.

## Implementation Risks
- **String Lifecycle**: Ensure string data passed into the C++ object is copied, not just referenced, to avoid dangling pointers if the source strings are temporary.

## Questions for C++ Team
- Should the Histogram be a shared pointer, unique pointer, or embedded value? (Likely embedded or unique_ptr given strict ownership).
