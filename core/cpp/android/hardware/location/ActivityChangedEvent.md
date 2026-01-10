# ActivityChangedEvent - Reverse Engineering Documentation

## Executive Summary
`ActivityChangedEvent` is a container class representing a batch of activity recognition events. It wraps a list of `ActivityRecognitionEvent` objects and implements `Parcelable` to be transferred across process boundaries, typically from the hardware abstraction layer to the framework or applications.

## Architecture Overview
- **Pattern**: Data Transfer Object (DTO) / Container.
- **Inheritance**: Implements `android.os.Parcelable`.
- **Composition**: Contains a list of `ActivityRecognitionEvent`.

## Detailed Functionality
- **Initialization**: Constructed with an array of `ActivityRecognitionEvent`s.
- **Immutability**: The internal list is effectively immutable after construction (wrapped in `Arrays.asList`, though the array itself isn't deeply copied in the constructor, the list view is fixed).
- **Serialization**: Writes the length of the array and then the typed array of events to the Parcel.

## Data Model
| Field | Type | Description |
|---|---|---|
| `mActivityRecognitionEvents` | `List<ActivityRecognitionEvent>` | The list of events in this batch. |

## API Reference
- `getActivityRecognitionEvents()`: Returns `Iterable<ActivityRecognitionEvent>`.
- `toString()`: formatting for debugging.

## Java-to-C++ Translation Guide
### Data Structure
```cpp
struct ActivityChangedEvent {
    std::vector<ActivityRecognitionEvent> activityRecognitionEvents;
};
```
### Serialization
- **Parceling**: Write size (int32), then loop write each `ActivityRecognitionEvent`.

## Questions for C++ Team
- None.
