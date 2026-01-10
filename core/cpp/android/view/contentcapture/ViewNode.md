# ViewNode - Reverse Engineering Documentation

## Executive Summary
A shadow representation of a `View` used for Content Capture. It mimics the structure of `AssistStructure.ViewNode` but is specialized for Content Capture (parcelable, flattened).

## Data Model
*   **Flags**: `mFlags` (long) encodes boolean properties (visibility, focus, clickability, etc.) and presence of other fields to optimize parceling.
*   **Properties**: `mText`, `mClassName`, `mId`, `mAutofillId`, `mBounds`, etc.
*   **Hierarchy**: `mParentAutofillId`.

## Key Algorithms
*   **Parceling**: Highly optimized `writeSelfToParcel`/`readFromParcel` using bitmasks to only write present fields.

## Java-to-C++ Translation Guide
*   **Optimization**: The bitmask-based serialization is complex and must be replicated exactly for IPC compatibility.
*   **Inner Class**: `ViewStructureImpl` implements `ViewStructure` to populate the `ViewNode`.
