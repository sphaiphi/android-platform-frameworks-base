# KeyDerivationParams - Reverse Engineering Documentation

## Executive Summary
`KeyDerivationParams` defines the algorithm used to derive a key from the user's lock screen input. Supports SHA-256 (salted) and SCRYPT.

## Architecture Overview
*   **Package**: `android.security.keystore.recovery`
*   **Type**: Class (Parcelable, System API)

## Data Model
*   `mAlgorithm`: `ALGORITHM_SHA256` (1) or `ALGORITHM_SCRYPT` (2).
*   `mSalt` (byte[]).
*   `mMemoryDifficulty` (int): For SCRYPT (N factor).

## Java-to-C++ Translation Guide
*   Struct.
