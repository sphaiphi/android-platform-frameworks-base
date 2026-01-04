# KeymasterBooleanArgument - Reverse Engineering Documentation

## Executive Summary
Represents a Keymaster argument with a boolean value (type `KM_BOOL`).

## Functionality
*   Value is implicitly `true` if the argument is present.
*   Does not write any payload to Parcel (only the tag is written by base class).

## Java-to-C++ Translation Guide
*   See `KeymasterArgument`.
