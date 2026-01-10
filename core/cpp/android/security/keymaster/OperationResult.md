# OperationResult - Reverse Engineering Documentation

## Executive Summary
`OperationResult` holds the result of a Keymaster cryptographic operation step (`begin`, `update`, or `finish`).

## Data Model
*   `resultCode` (int).
*   `token` (IBinder): Token for the operation session.
*   `operationHandle` (long): Handle ID.
*   `inputConsumed` (int): Number of bytes processed.
*   `output` (byte[]): Output data.
*   `outParams` (KeymasterArguments): Output parameters.

## Java-to-C++ Translation Guide
*   Maps to the return values of HAL methods like `begin`, `update`, `finish`.
