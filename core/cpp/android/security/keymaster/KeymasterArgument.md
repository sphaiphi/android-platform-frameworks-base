# KeymasterArgument - Reverse Engineering Documentation

## Executive Summary
`KeymasterArgument` is an abstract base class for Keymaster tag arguments. It wraps a tag ID and handles parceling.

## Architecture Overview
*   **Package**: `android.security.keymaster`
*   **Type**: Abstract Class (Parcelable)
*   **Subclasses**: `KeymasterIntArgument`, `KeymasterLongArgument`, `KeymasterBooleanArgument`, `KeymasterBlobArgument`, `KeymasterDateArgument`.

## Data Model
*   `tag` (int): The Keymaster tag ID (including type).

## Serialization
*   **Write**: Writes tag, then delegates value writing to subclass.
*   **Read**: Reads tag, determines type from tag bits (`KeymasterDefs.getTagType`), instantiates correct subclass.

## Java-to-C++ Translation Guide
*   C++ Keymaster HAL uses a `keymaster_key_param_t` struct (C-style union) or C++ classes.
*   This hierarchy essentially mimics the tagged union structure of Keymaster parameters.
