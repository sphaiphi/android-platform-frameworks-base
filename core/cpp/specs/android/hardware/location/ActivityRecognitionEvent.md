# ActivityRecognitionEvent - Reverse Engineering Documentation

## Executive Summary
`ActivityRecognitionEvent` represents a single detected activity event, containing the activity name (e.g., "walking", "running"), the event type (e.g., entered, exited), and a timestamp.

## Architecture Overview
- **Pattern**: Value Object.
- **Inheritance**: Implements `android.os.Parcelable`.

## Detailed Functionality
- **Data Holder**: Stores activity string, event type integer, and timestamp (nanoseconds).
- **Immutability**: All fields are `final`.

## Data Model
| Field | Type | Description |
|---|---|---|
| `mActivity` | `String` | The name of the activity. |
| `mEventType` | `int` | The type of event (e.g., flush complete, etc. - though constants aren't defined here). |
| `mTimestampNs` | `long` | Timestamp in nanoseconds. |

## API Reference
- `getActivity()`: Returns activity name.
- `getEventType()`: Returns event type.
- `getTimestampNs()`: Returns timestamp.

## Java-to-C++ Translation Guide
### Data Structure
```cpp
struct ActivityRecognitionEvent {
    std::string activity;
    int32_t eventType;
    int64_t timestampNs;
};
```

## Questions for C++ Team
- Where are the event type constants defined in the native layer? (Likely `ActivityRecognitionProvider` or HAL definitions).
