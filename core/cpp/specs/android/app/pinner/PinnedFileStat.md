# PinnedFileStat - Reverse Engineering Documentation

## Executive Summary
`PinnedFileStat` is an immutable data class (Parcelable) used to transport statistical information about files pinned in memory by the `PinnerService`. It allows clients to query which files are pinned, their size, and their associated group.

## Architecture Overview
*   **Type**: Data Transfer Object (DTO) / Value Object.
*   **Interface**: Implements `android.os.Parcelable`.
*   **Scope**: Part of the `android.app.pinner` package, exposed via `IPinnerService`.

## Detailed Functionality

### Data Holding
**Purpose**: Encapsulates three specific pieces of metadata regarding a pinned file.
**Attributes**:
1.  `filename`: The path or name of the file.
2.  `bytesPinned`: The number of bytes of the file that are pinned in memory.
3.  `groupName`: An identifier for the group this file belongs to (e.g., "boot", "app").

### Serialization (Parcelable)
**Purpose**: Enables instances to be transferred across process boundaries (IPC) via Binder.
**Algorithm**:
*   **Write**: Writes fields to the `Parcel` in a specific order: `filename`, `bytesPinned`, `groupName`.
*   **Read**: Reads fields from the `Parcel` in the same order.

## Data Model

| Java Field | Type | C++ Equivalent | Description |
| :--- | :--- | :--- | :--- |
| `filename` | `String` | `android::String8` or `std::string` | Name/Path of the pinned file. Serialized as UTF-8. |
| `bytesPinned` | `long` | `int64_t` | Size of the pinned memory in bytes. |
| `groupName` | `String` | `android::String8` or `std::string` | Group identifier. Serialized as UTF-8. |

## API Reference

### Constructors
*   `PinnedFileStat(@NonNull String filename, long bytesPinned, @NonNull String groupName)`: Initializes all fields.

### Getters
*   `getFilename()`: Returns the filename.
*   `getBytesPinned()`: Returns the pinned size in bytes.
*   `getGroupName()`: Returns the group name.

### Parcelable Methods
*   `writeToParcel(Parcel dest, int flags)`: Serializes the object.
*   `describeContents()`: Returns 0 (no special file descriptors).
*   `createFromParcel(Parcel source)`: Factory method for deserialization.

## Java-to-C++ Translation Guide

### Data Structure
Define a C++ struct or class to hold the data.

```cpp
struct PinnedFileStat : public android::Parcelable {
    std::string filename;
    int64_t bytesPinned;
    std::string groupName;
    
    // Implement readFromParcel and writeToParcel
};
```

### Serialization Logic
The Java implementation uses `writeString8` and `readString8`. This indicates specific encoding expectations (UTF-8).

**C++ Write Implementation**:
```cpp
android::status_t writeToParcel(android::Parcel* parcel) const override {
    parcel->writeUtf8AsUtf16(filename); // Verify Parcel::writeString8 equivalent in C++
    // Note: Java's Parcel.writeString8 writes a UTF-8 string. 
    // In C++ Parcel, writeUtf8AsUtf16 is common for interoperability if the Java side expects String8 
    // BUT check strict matching. Java `writeString8` specifically writes "A UTF-8 string".
    // C++ `Parcel::writeString8` exists.
    
    parcel->writeString8(android::String8(filename.c_str()));
    parcel->writeInt64(bytesPinned);
    parcel->writeString8(android::String8(groupName.c_str()));
    return android::OK;
}
```

**C++ Read Implementation**:
```cpp
android::status_t readFromParcel(const android::Parcel* parcel) override {
    android::String8 tmpFn;
    parcel->readString8(&tmpFn);
    filename = tmpFn.string();
    
    parcel->readInt64(&bytesPinned);
    
    android::String8 tmpGn;
    parcel->readString8(&tmpGn);
    groupName = tmpGn.string();
    
    return android::OK;
}
```

*Warning*: Verify `Parcel::writeString8` behavior matches Java's `writeString8`. Java's `writeString8` writes a UTF-8 string directly. C++ `writeString8` does the same.

## Test Cases & Validation

### Case 1: Serialization Round-Trip
*   **Input**: `filename="libart.so"`, `bytesPinned=1048576`, `groupName="boot"`
*   **Expected Serialization**:
    1.  String8: "libart.so"
    2.  Int64: 1048576
    3.  String8: "boot"
*   **Output**: New object equal to input.

## Implementation Risks
1.  **String Encoding**: Ensure strict alignment between Java `writeString8` and C++ `readString8`.
2.  **Null Handling**: Java fields are annotated `@NonNull`. C++ should enforce this or handle empty strings gracefully.
3.  **Data Alignment**: `long` is always 64-bit. Ensure C++ uses `int64_t`.
