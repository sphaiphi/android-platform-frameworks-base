# EventList - Reverse Engineering Documentation

## Executive Summary
`EventList` is a specialized container for `UsageEvents.Event` objects. It guarantees that events are always stored in non-descending order of their timestamps.

## Architecture Overview
- **Data Structure**: Wraps an `ArrayList<UsageEvents.Event>`.
- **Algorithm**: Insertion sort logic.

## Detailed Functionality

### Insertion Logic (`insert`)
**Purpose**: Insert an event while maintaining sort order.
**Algorithm**:
1.  **Optimization**: Check if the list is empty or if the new event's timestamp is >= the last event's timestamp. If so, `add` to the end.
2.  **Search**: If not appended, find the insertion index using `firstIndexOnOrAfter`.
3.  **Add**: Insert at the found index.

### Binary Search (`firstIndexOnOrAfter`)
**Purpose**: Find the first index where `event.mTimeStamp >= targetTimeStamp`.
**Algorithm**: Standard binary search. Returns `size` if not found (i.e., target is greater than all elements).

### Merge Logic (`merge`)
**Purpose**: Merge another sorted `EventList` into this one.
**Algorithm**: Iterates through the input list and calls `insert` for each element.
*Note*: This is O(N*M) or O(N log M) depending on implementation details, effectively repeated insertion. Since both are sorted, a merge-sort style merge (linear time) would be more efficient, but the current implementation uses repeated insertion.

## Data Model
- `mEvents`: `ArrayList<UsageEvents.Event>`.

## API Reference
- `size()`, `clear()`, `get(index)`.
- `insert(Event)`.
- `remove(index)`: Returns null on out-of-bounds.
- `firstIndexOnOrAfter(long)`.
- `merge(EventList)`.

## Java-to-C++ Translation Guide
- **Container**: `std::vector<UsageEvents::Event>`.
- **Algorithms**:
    - Use `std::upper_bound` or `std::lower_bound` for the binary search.
    - `insert`: `vector::insert`.
- **Thread Safety**: The Java class is not synchronized. C++ should likely remain unsynchronized unless required.

## Test Cases & Validation
1.  **Sort Order**: Insert events with timestamps `[10, 5, 20]`. Verify list order is `[5, 10, 20]`.
2.  **Duplicate Timestamps**: Insert `[10, 10]`. Verify stability (though functionality just requires time order).

## Implementation Risks
- **Performance**: The `merge` implementation in Java is suboptimal for large lists (repeated insertions shift elements). A C++ implementation might choose to optimize this using `std::merge` into a new vector if performance is critical, but strictly mimicking logic implies repeated insertion.
