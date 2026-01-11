# DhcpClientEvent.java - Reverse Engineering Documentation

## Executive Summary
`DhcpClientEvent` is a deprecated event logging state transitions in the DHCP client state machine.

## Architecture Overview
- **Type**: Parcelable Metrics Event
- **Package**: `android.net.metrics`.

## Data Model
-   `msg`: State name or message.
-   `durationMs`: Duration.

## Java-to-C++ Translation Guide
Simple struct.
