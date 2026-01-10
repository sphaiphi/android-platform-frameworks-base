# WifiDisplaySessionInfo - Reverse Engineering Documentation

## Executive Summary
`WifiDisplaySessionInfo` contains technical details about an active Miracast session, primarily used for certification and debugging.

## Data Model
- `mClient`: Boolean (Client vs Owner).
- `mSessionId`: Int.
- `mGroupId`: String.
- `mPassphrase`: String.
- `mIP`: String (IP Address).

## Java-to-C++ Translation Guide
- Simple Parcelable struct.
