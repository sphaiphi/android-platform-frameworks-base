# NotificationHistory - Reverse Engineering Documentation

## Executive Summary
`NotificationHistory` is a specialized container used to store and iterate over historical notification data. It is primarily used for the "Notification History" feature in Android, which allows users to see dismissed notifications. It employs a string pooling mechanism to optimize parcel size during IPC.

## Architecture Overview
- **Core Components**:
    - `HistoricalNotification`: Inner class representing a single recorded notification entry.
    - `mStringPool`: An array of strings used to deduplicate package names, channel names, and IDs across multiple notification entries.
    - `mParcel`: Internal buffer for efficient streaming of notification data.
- **Serialization**: Implements `Parcelable`. It writes its internal data as a `Blob` to handle potentially large histories efficiently (using ashmem if necessary).

## Detailed Functionality

### HistoricalNotification
**Purpose**: Stores snapshot data of a notification at the time it was posted.
**Stored Data**: Package name, Uid, UserID, Title, Text, Icon, Channel ID/Name, Conversation ID, and Posted Timestamp.

### String Pooling
**Purpose**: Reduces memory and IPC overhead.
**Algorithm**:
1. Before writing to a parcel, `poolStringsFromNotifications()` identifies all unique strings.
2. `getPooledStringsToWrite()` returns a sorted array of these strings.
3. Individual notification entries store integer indices into this pool instead of full strings.

### Parceling Logic
**Purpose**: Efficiently transfers history across processes.
**Mechanism**:
- `writeToParcel`: Writes count, current index, string pool, and then a sequence of notification entries.
- `NotificationHistory(Parcel in)`: Reads the entire history into a temporary `Parcel` and initializes the string pool. `getNextNotification()` then reads from this internal parcel on demand.

## API Reference
- `public boolean hasNextNotification()`: Iterator check.
- `public HistoricalNotification getNextNotification()`: Iterator access.
- `public void addNotificationToWrite(HistoricalNotification n)`: Adds a new entry.
- `public void removeNotificationsFromWrite(String packageName)`: Bulk removal for a package.

## Java-to-C++ Translation Guide
- **String Pool**: Use a `std::vector<std::string>` and a `std::map<std::string, int>` to manage the pool and index lookups.
- **Blob Parceling**: Use `Parcel::writeBlob` and `Parcel::readBlob` in C++ to match the Java side's handling of large data buffers.
- **Memory Management**: The `mParcel` in Java is explicitly recycled. In C++, ensure `Parcel` objects and pooled strings are handled via RAII.

## Implementation Risks
- **Index Offsets**: The binary format of the notification entries in the parcel must be strictly matched between Java and C++.
- **Icon Handling**: The current Java implementation has commented-out icon parceling ("The current design does not display icons"). C++ implementation should match this unless icon support is added.
- **Data Size**: Very large histories can exceed binder transaction limits. The use of `Blob` (which falls back to ashmem) is mandatory for stability.
