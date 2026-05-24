# CellBroadcastIntents - Reverse Engineering Documentation

## Executive Summary
`CellBroadcastIntents` is a static helper class designed to centralize the creation and broadcasting of intents related to Cell Broadcast messages (SMS-CB) and Area Info updates. It ensures that specific extras (like slot index and subscription ID) are consistently attached and that broadcasts are sent to the correct users with appropriate permissions.

## Architecture Overview
*   **Type**: Static Utility Class (System API).
*   **Role**: Intent Factory and Broadcaster.
*   **Dependencies**: `Context`, `Intent`, `UserHandle`, `AppOpsManager`.

## Detailed Functionality

### 1. SMS-CB Broadcast (`sendSmsCbReceivedBroadcast`)
*   **Action**: `Telephony.Sms.Intents.SMS_CB_RECEIVED_ACTION`.
*   **Permissions**:
    *   Receiver requires `Manifest.permission.RECEIVE_SMS`.
    *   AppOp checked: `AppOpsManager.OPSTR_RECEIVE_SMS`.
*   **Extras**:
    *   `message`: The `SmsCbMessage` object.
    *   `phone`, `android.telephony.extra.SLOT_INDEX`: The physical slot index.
    *   `subscription`, `android.telephony.extra.SUBSCRIPTION_INDEX`: The subId (if valid).
*   **Targeting**: Supports broadcasting to a specific user (`UserHandle`) or the system context.

### 2. Area Info Update
*   **Constant**: `ACTION_AREA_INFO_UPDATED`.
*   **Usage**: Used to notify that `CellBroadcastService#getCellBroadcastAreaInfo(int)` has new data.

## Java-to-C++ Translation Guide
*   **Intent Construction**: In C++ (Android system services), this maps to creating an `Intent` object (usually via JNI or a native framework equivalent if available) and calling `ActivityManagerService` or `Context` equivalent to broadcast.
*   **Constants**: Define string constants for actions and extras in a header file.
*   **Logic**: The logic is primarily about bundling data into an IPC message (Intent).

## Implementation Risks
*   **Permission Enforcement**: The C++ implementation must ensure it asserts the `RECEIVE_SMS` permission when broadcasting, matching the Java behavior.
