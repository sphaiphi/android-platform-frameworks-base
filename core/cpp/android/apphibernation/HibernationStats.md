# HibernationStats - Reverse Engineering Documentation

## Executive Summary
`HibernationStats` is a simple data container class used to transport statistics regarding app hibernation, specifically focusing on storage savings. It is `Parcelable`, allowing it to be transferred across IPC boundaries (e.g., from System Server to Client).

## Data Model

### Fields
- `long mDiskBytesSaved`: Represents the amount of disk space (in bytes) saved by hibernating the package.

## API Reference

### Accessors
- `getDiskBytesSaved()`: Returns `long`.

### Parcelable Implementation
- **writeToParcel**: Writes the single `long` field.
- **createFromParcel**: Reads the single `long` field.

## Java-to-C++ Translation Guide
- **Equivalent Structure**: A simple C++ struct or class.
- **Serialization**: Standard AIDL parceling logic for a 64-bit integer (`int64_t` in C++).

```cpp
struct HibernationStats {
    int64_t diskBytesSaved;
};
```
