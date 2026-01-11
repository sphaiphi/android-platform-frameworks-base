# MessagePdu - Reverse Engineering Documentation

## Executive Summary
`MessagePdu` is a simple Parcelable wrapper around a list of byte arrays, representing the Protocol Data Units (PDUs) of an SMS message (which might be multi-part).

## Data Model

### Fields
*   `mPduList`: `List<byte[]>` - The list of PDUs.

## API Reference

### Getters
*   `getPdus()`: Returns the list.

## Java-to-C++ Translation Guide

### Parcelable
*   **Java**: Writes size, then loops to write byte arrays.
*   **C++**: `android::Parcelable`. Vector of `std::vector<uint8_t>` or similar.

## Implementation Notes
*   **Immutable**: Created with a list, cannot be modified.
