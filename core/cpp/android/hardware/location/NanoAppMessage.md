# NanoAppMessage - Reverse Engineering Documentation

## Executive Summary
`NanoAppMessage` represents a message exchanged between the Context Hub and a client. It encapsulates the payload, message type, and routing information (Broadcast vs Unicast, Reliable vs Unreliable).

## Architecture Overview
- **Pattern**: Message / DTO.
- **Inheritance**: Implements `android.os.Parcelable`.

## Detailed Functionality
- **Factories**: `createMessageToNanoApp`, `createMessageFromNanoApp`.
- **Properties**:
  - `mNanoAppId`: Source or Destination ID.
  - `mMessageType`: Application-specific type code.
  - `mMessageBody`: Raw byte payload.
  - `mIsBroadcasted`: True if multicast.
  - `mIsReliable`: True if ACK required.
  - `mMessageSequenceNumber`: For reliability tracking.

## Data Model
| Field | Type | Description |
|---|---|---|
| `mNanoAppId` | `long` | App ID. |
| `mMessageType` | `int` | Type. |
| `mMessageBody` | `byte[]` | Payload. |
| `mIsReliable` | `boolean` | Reliability flag. |

## Java-to-C++ Translation Guide
- **Data Structure**: Struct.
- **Usage**: Core messaging primitive.

## Questions for C++ Team
- None.
