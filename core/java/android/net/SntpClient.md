# SntpClient.java - Reverse Engineering Documentation

## Executive Summary
`SntpClient` is a simple SNTP (Simple Network Time Protocol) client. It requests time from an NTP server and computes the offset between the device's monotonic clock and the NTP time, as well as the round-trip time.

## Architecture Overview
- **Type**: Network Client
- **Package**: `android.net`
- **Protocol**: SNTP (RFC 4330 / 2030).

## Detailed Functionality

### Request Logic
1.  **Socket**: Creates a `DatagramSocket`.
2.  **Packet**: Constructs a 48-byte NTP packet.
    -   Mode: Client (3).
    -   Version: 3.
    -   Transmit Timestamp: Randomly fuzzed current time (for matching response).
3.  **Send/Receive**: Sends to server, waits for response (timeout).
4.  **Processing**:
    -   Validates response (Mode=Server/Broadcast, Stratum!=0, Transmit/Originate match).
    -   Calculates **Round Trip Time**: `(response_ticks - request_ticks) - (server_transmit - server_receive)`.
    -   Calculates **Clock Offset**: `((receive - request) + (transmit - response)) / 2`.
5.  **Result**: Stores `mNtpTime`, `mNtpTimeReference` (boot time), and `mRoundTripTime`.

### Data Formats
-   **Timestamp64**: NTP uses 64-bit timestamps (32-bit seconds since 1900, 32-bit fraction).
-   **Endianness**: Network byte order (Big Endian).

## Java-to-C++ Translation Guide
Standard socket programming.
-   `socket(AF_INET, SOCK_DGRAM, 0)`.
-   `sendto`, `recvfrom`.
-   NTP Packet struct (48 bytes).
-   Manual serialization/deserialization of big-endian 64-bit fixed-point numbers.

## Implementation Risks
-   **Y2036**: NTP era handling (1900 vs 2036). The Java code handles era folding logic in `Timestamp64`. C++ implementation must match this to avoid issues around era rollover.
-   **Concurrency**: Class is noted as "not thread-safe".
