# KeymasterBlob - Reverse Engineering Documentation

## Executive Summary
`KeymasterBlob` is a simple wrapper around a byte array, used for parceling opaque binary blobs (like keys or nonces) in Keymaster calls.

## Data Model
*   `blob` (byte[]).

## Java-to-C++ Translation Guide
*   `std::vector<uint8_t>`.
