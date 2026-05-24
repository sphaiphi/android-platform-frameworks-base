# HubMessage - Reverse Engineering Documentation

## Executive Summary
`HubMessage` is a Parcelable class representing a generic data message sent between endpoints. It contains the raw payload, a type identifier, and sequence/flag metadata.

## Architecture Overview
- **Type**: Parcelable Data Class.
- **Package**: `android.hardware.contexthub`.

## Detailed Functionality
- **Content**: `mMessageType` (int) and `mMessageBody` (byte array).
- **Flow Control**: `mResponseRequired` flag indicates if the sender awaits an acknowledgement.
- **Sequencing**: `mMessageSequenceNumber` used for tracking delivery (assigned by system service).

## Data Model
- `mMessageType`: `int`
- `mMessageBody`: `byte[]`
- `mResponseRequired`: `boolean`
- `mMessageSequenceNumber`: `int`

## Java-to-C++ Translation Guide
### C++ Equivalent
```cpp
struct HubMessage {
    int32_t messageType;
    std::vector<uint8_t> messageBody;
    bool responseRequired;
    int32_t messageSequenceNumber;
};
```
### Implementation Guidance
- Ensure the Parcel read/write order matches the Java implementation.
- `DEBUG_LOG_NUM_BYTES` constant suggests a logging helper might be useful in C++ as well.
