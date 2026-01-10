# WrappedApplicationKey - Reverse Engineering Documentation

## Executive Summary
`WrappedApplicationKey` represents a single application key that has been encrypted (wrapped) with the Recovery Key.

## Data Model
*   `mAlias` (String): Keystore alias.
*   `mEncryptedKeyMaterial` (byte[]): The wrapped key.
*   `mMetadata` (byte[]): Associated metadata (auth/unencrypted).

## Java-to-C++ Translation Guide
*   Simple struct.
