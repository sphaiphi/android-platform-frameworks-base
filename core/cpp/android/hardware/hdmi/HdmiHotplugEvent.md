# HdmiHotplugEvent - Reverse Engineering Documentation

## Executive Summary
`HdmiHotplugEvent` represents a hotplug event on an HDMI port. It contains the port number and the connection status.

## Architecture Overview
- **Type**: Immutable Data Class / Parcelable.
- **System API**: `@SystemApi`.

## Detailed Functionality
- **Fields**:
    - `mPort` (int): Port ID.
    - `mConnected` (boolean): Connection state (`true` = connected).
- **Parcelable**: Serializes port and connected boolean (as byte).

## Java-to-C++ Translation Guide
- **Class**: Simple C++ struct or class.
- **Parcelable**: Implement `android::os::Parcelable`.

