# SharedPreferencesImpl - Reverse Engineering Documentation

## Executive Summary
`SharedPreferencesImpl` is the primary implementation of the `SharedPreferences` interface. It provides a lightweight, persistent key-value store for primitive data types and strings. It uses XML files for storage and employs an optimistic in-memory caching mechanism with asynchronous background writes to balance performance and durability. It also handles file-level backups during writes to ensure data integrity.

## Architecture Overview
- **Core Components**:
    - `mFile`: The actual XML storage file.
    - `mBackupFile`: A `.bak` file used for atomic write safety.
    - `mMap`: In-memory cache of all key-value pairs.
    - `mListeners`: Weak-reference map of change listeners.
    - `mWritingToDiskLock`: Serializes disk access.
- **Threading Model**: 
    - `sLoadExecutor`: Single-thread pool for loading from disk.
    - `QueuedWork`: Global system for ensuring background writes finish before the process exits.

## Detailed Functionality

### Loading from Disk (`loadFromDisk`)
**Purpose**: Initializes the in-memory map.
**Algorithm**:
1. Checks for a backup file. If it exists, it means the previous write failed; it restores the backup and deletes the corrupted file.
2. Reads the XML file using `XmlUtils.readMapXml`.
3. Notifies all waiting threads (`notifyAll`) once the map is ready.

### Editing and Committing (`EditorImpl`)
**Mechanism**:
- `apply()`: Commits changes to the in-memory map immediately and schedules an asynchronous disk write. It is preferred for most UI tasks.
- `commit()`: Synchronously writes changes to disk and returns success/failure.
- `commitToMemory()`: Performs the actual delta application to the map and returns a `MemoryCommitResult`.

### Write Strategy (`writeToFile`)
**Purpose**: Atomic and durable storage.
**Algorithm**:
1. Renames the current file to the `.bak` file.
2. Creates a `FileOutputStream` for the main file.
3. Serializes the map to XML.
4. Performs an `fsync` (`FileUtils.sync`) to ensure the OS has persisted the bits.
5. Deletes the backup file.
6. If any step fails, it attempts to delete the partial file so the backup can be restored on the next load.

### Change Notification
**Logic**: Tracks which keys were modified during a commit. Invokes listeners on the main thread. Supports `null` key notifications when `clear()` is called (Android R+).

## API Reference
- `public String getString(String key, String defValue)`: Value retrieval.
- `public Editor edit()`: Returns an editor.
- `public void apply()`: Async commit.
- `public boolean commit()`: Sync commit.

## Java-to-C++ Translation Guide
- **Key-Value Store**: Use `std::map<std::string, std::any>` or a specialized variant map for the in-memory cache.
- **XML Serialization**: Use a native XML library (e.g., `libxml2`) or a simple custom serializer that matches the Android `map` XML format.
- **File System**: Use standard POSIX `rename`, `fsync`, and `stat` calls.
- **Synchronization**: Replicate the two-lock pattern (`mLock` for map access, `mWritingToDiskLock` for I/O) to avoid blocking reads during writes.

## Implementation Risks
- **Data Corruption**: Atomic file replacement logic (`.bak` restoration) is critical. C++ implementation must match this exactly to avoid data loss.
- **Performance**: Excessive `fsync` calls can kill performance. The Java side uses `MAX_FSYNC_DURATION_MILLIS` (256ms) as a warning threshold.
- **Memory Pressure**: For large preference files, the in-memory map can consume significant RAM. C++ logic might need a mechanism to purge the cache if memory is low (though the current Java implementation doesn't do this).
