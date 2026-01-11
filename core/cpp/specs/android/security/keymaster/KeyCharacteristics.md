# KeyCharacteristics - Reverse Engineering Documentation

## Executive Summary
`KeyCharacteristics` holds the characteristics of a key, separated into those enforced by secure hardware (`hwEnforced`) and those enforced by software (Keystore daemon) (`swEnforced`).

## Architecture Overview
*   **Package**: `android.security.keymaster`
*   **Type**: Class (Parcelable)
*   **Components**: Two `KeymasterArguments` lists.

## Detailed Functionality
*   **Accessors**: `getEnum`, `getEnums`, `getUnsignedInt`, `getUnsignedLongs`, `getDate`, `getBoolean`.
*   **Logic**: Checks `hwEnforced` first, then `swEnforced`.

## Java-to-C++ Translation Guide
*   Maps to the `KeyCharacteristics` structure in the Keymaster/KeyMint HAL (which typically has a list of authorizations).
*   In C++, this might be a single list with tag types indicating enforcement, or two separate lists as here.
