# Telephony - Reverse Engineering Documentation

## Executive Summary
`Telephony` is the contract for the Telephony/SMS/MMS provider. It defines tables for SMS messages, MMS messages, threads (conversations), and carriers (APNs).

## Architecture Overview
- **Authority**: `sms`, `mms`, `mms-sms`.
- **Inner Classes**: `Sms`, `Mms`, `Threads`, `Carriers`, `MmsSms`.

## Detailed Functionality
-   **Sms**:
    -   `Inbox`, `Sent`, `Draft`, `Outbox`.
    -   Columns: `address`, `body`, `date`, `read`, `type`, `thread_id`.
    -   Intents: `SMS_DELIVER_ACTION`, `SMS_RECEIVED_ACTION`.
-   **Mms**:
    -   Complex structure with `Pdu` (headers) and `Part` (body).
-   **Threads**: Summarizes conversations (`message_count`, `snippet`).
-   **Carriers**: APN settings (`apn`, `proxy`, `port`, `mmsc`).

## API Reference
-   `Sms.CONTENT_URI`.
-   `Sms.addMessageToUri`.
-   `Sms.getDefaultSmsPackage`.

## Java-to-C++ Translation Guide
-   **SMS PDUs**: Handling raw PDUs (`byte[]`) is common in C++ telephony stacks. The `getMessagesFromIntent` logic parses these.
-   **Database Access**: Standard SQLite-backed provider access.
