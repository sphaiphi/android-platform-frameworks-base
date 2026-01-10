# CarrierMessagingService - Reverse Engineering Documentation

## Executive Summary
`CarrierMessagingService` is an abstract service that allows a carrier app to intercept, filter, and handle SMS and MMS messages. It enables carriers to implement features like spam filtering or carrier-specific messaging logic.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC**: Implements `ICarrierMessagingService.Stub` via an internal wrapper class `ICarrierMessagingWrapper`.
*   **Manifest**: Requires `android.permission.BIND_CARRIER_SERVICES` and `SERVICE_INTERFACE`.
*   **Permissions**: Only bound if the app has carrier privileges.

## Detailed Functionality

### Core Operations
1.  **Filtering Inbound SMS**: `onReceiveTextSms` (replacing `onFilterSms`) allows the service to inspect incoming SMS and decide whether to drop them or pass them to the default SMS app.
2.  **Sending SMS/MMS**: `onSendTextSms`, `onSendDataSms`, `onSendMultipartTextSms`, `onSendMms` allow the service to handle the actual sending over the network, potentially using carrier-specific protocols or logic.
3.  **Downloading MMS**: `onDownloadMms` handles MMS content retrieval.

### `onBind(Intent intent)`
**Purpose**: Binds the service.
**Returns**: `ICarrierMessagingService` stub if intent action matches.

### `ICarrierMessagingWrapper`
*   Maps AIDL calls to the abstract methods of the class.
*   Handles callbacks (`ICarrierMessagingCallback`) by wrapping them in `ResultCallback`.

### Abstract/Overridable Methods
*   `onReceiveTextSms`: Filter incoming text SMS. Returns bitmask (KEEP vs DROP).
*   `onSendTextSms`/`onSendDataSms`/`onSendMultipartTextSms`: Intercept outgoing SMS. Can return `SEND_STATUS_RETRY_ON_CARRIER_NETWORK` to let the platform handle it via standard RIL, or handle it internally.
*   `onSendMms`/`onDownloadMms`: Intercept MMS operations.

## Data Model

### Result Codes
*   **Receive Options**: `RECEIVE_OPTIONS_DEFAULT`, `RECEIVE_OPTIONS_DROP`, `RECEIVE_OPTIONS_SKIP_NOTIFY...`
*   **Send Status**: `SEND_STATUS_OK`, `SEND_STATUS_RETRY_ON_CARRIER_NETWORK`, `SEND_STATUS_ERROR`.
*   **Download Status**: `DOWNLOAD_STATUS_OK`, `DOWNLOAD_STATUS_RETRY_ON_CARRIER_NETWORK`, `DOWNLOAD_STATUS_ERROR`.

### Inner Classes
*   **`SendSmsResult`**: Status + Message Reference.
*   **`SendMultipartSmsResult`**: Status + Array of Message References.
*   **`SendMmsResult`**: Status + SendConf PDU.

## Java-to-C++ Translation Guide

### IPC
*   **Java**: `ICarrierMessagingService.Stub` via wrapper.
*   **C++**: `BnCarrierMessagingService`.

### PDUs
*   **Java**: `MessagePdu` (Parcelable wrapping `byte[]`).
*   **C++**: Need to handle raw byte arrays for PDUs.

### Callbacks
*   **Java**: `ResultCallback` interface wrapping `ICarrierMessagingCallback`.
*   **C++**: Holds `sp<ICarrierMessagingCallback>` and invokes `onFilterComplete`, `onSendSmsComplete`, etc.

## Implementation Risks
*   **Latency**: Filtering SMS happens on the critical path of SMS delivery. Slow service implementation delays SMS reception.
*   **Reliability**: If the service crashes or fails, SMS/MMS might be lost or stuck.
