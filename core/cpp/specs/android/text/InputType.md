# InputType - Reverse Engineering Documentation

## Executive Summary
Defines constants for input content types (Text, Number, Phone, DateTime) and their variations/flags.

## Data Model
- **Masks**: `TYPE_MASK_CLASS`, `TYPE_MASK_VARIATION`, `TYPE_MASK_FLAGS`.
- **Classes**: `TYPE_CLASS_TEXT`, `TYPE_CLASS_NUMBER`, etc.
- **Flags**: `TYPE_TEXT_FLAG_CAP_SENTENCES`, `TYPE_TEXT_FLAG_MULTI_LINE`, etc.

## Java-to-C++ Translation Guide
- **Enums**: Header file with bitmask constants.
