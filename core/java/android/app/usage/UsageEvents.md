# UsageEvents - Reverse Engineering Documentation

## Executive Summary
`UsageEvents` is a container/iterator for a collection of `UsageEvents.Event` objects. It allows iterating over a sequence of events returned by `UsageStatsManager`. It employs optimizations like string pooling and different parceling strategies (blob vs parceled list) to handle large data sets efficiently.

## Architecture Overview
- **Pattern**: Iterator.
- **Data Source**: Can be backed by an in-memory list (`mEventsToWrite`) or a `Parcel` (`mParcel`) for reading.
- **Inner Class**: `UsageEvents.Event` (The data item).

## Detailed Functionality

### Inner Class: `Event`
- **Fields**: Package, Class, Timestamp, EventType, Configuration, etc.
- **Obfuscation**: Methods like `getObfuscatedIfInstantApp` hide data for instant apps.
- **Parceling**: Writes fields.

### Storage Strategy
1.  **Parceled List (Flagged)**: Uses `ParcelableUsageEventList` to handle large lists via Binder side-channel.
2.  **Blob (Legacy/Default)**:
    - Writes the String Pool (array of unique strings).
    - Writes all events into a temporary Parcel.
    - Writes that temporary Parcel's bytes as a Blob to the main Parcel.
    - **Reading**: Reads the Blob, unmarshals to a Parcel, reads String Pool, then reads events one by one from that Parcel.

### String Pooling
**Purpose**: Reduce IPC size by not repeating package/class names.
**Mechanism**:
- **Write**: Create a `String[]` pool. Write indices into this pool instead of full strings for package/class names.
- **Read**: Read the pool. Look up strings by index.

### Iteration (`getNextEvent`)
- Checks if backed by List or Parcel.
- If List: Return next element.
- If Parcel: Read next element from the internal `mParcel`.

## Data Model
- `mStringPool`: `String[]`.
- `mEventCount`: Total events.
- `mIndex`: Current iterator position.
- `mParcel`: The Parcel containing event data (if reading from blob).
- `mEventsToWrite`: List (if writing or reading from ParceledList).

## Java-to-C++ Translation Guide
- **String Pool**: Essential for compatibility. The C++ reader must read the string array first, then use indices to resolve strings.
- **Blob Handling**: Must handle `unmarshall` logic to read the embedded Parcel data.
- **Flags**: Check `Flags.useParceledList()` to determine which read path to use.

## Implementation Risks
- **Blob Format**: The layout of the data inside the blob (String array followed by events) must be replicated exactly.
- **Parcel Lifecycle**: Managing the lifetime of the temporary `mParcel` (or its C++ equivalent) during iteration.
