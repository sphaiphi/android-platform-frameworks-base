# ExportResult - Reverse Engineering Documentation

## Executive Summary
`ExportResult` is a Parcelable container for the result of a Keymaster key export operation. It contains the result code and the exported key data blob.

## Data Model
*   `resultCode` (int): The error code (or 0 for success).
*   `exportData` (byte[]): The exported key material (if successful).

## Java-to-C++ Translation Guide
*   Simple struct.
*   Direct mapping to Keymaster HAL return types.
