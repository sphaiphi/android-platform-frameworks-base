# KeymasterArguments - Reverse Engineering Documentation

## Executive Summary
`KeymasterArguments` is a collection of `KeymasterArgument` objects. It allows constructing a list of parameters to pass to Keymaster operations (generation, import, operation start).

## Architecture Overview
*   **Package**: `android.security.keymaster`
*   **Type**: Class (Parcelable)
*   **Internals**: `List<KeymasterArgument>`.

## Functionality
*   **Builders**: `addEnum`, `addUnsignedInt`, `addUnsignedLong`, `addBoolean`, `addBytes`, `addDate`.
*   **Accessors**: `getEnum`, `getBytes`, etc.
*   **Serialization**: Writes the list to the Parcel.

## Java-to-C++ Translation Guide
*   Maps to `std::vector<keymaster_key_param_t>` or `hidl_vec<KeyParameter>` in HAL interfaces.
