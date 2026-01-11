# FragmentState - Reverse Engineering Documentation

## Executive Summary
`FragmentState` is a Parcelable class used to snapshot a Fragment's state (class name, index, saved bundle) so it can be completely destroyed and later reconstructed (instantiated).

## Architecture Overview
*   **Type**: Parcelable Data Class.
*   **Fields**: `mClassName`, `mIndex`, `mFromLayout`, `mFragmentId`, `mContainerId`, `mTag`, `mRetainInstance`, `mDetached`, `mArguments`, `mHidden`, `mSavedFragmentState`.

## Detailed Functionality
*   **Constructor**: Takes a `Fragment` and copies fields.
*   **Instantiation**: `instantiate()` recreates the Fragment object and restores fields.

## Java-to-C++ Translation Guide
*   Serialization logic.
*   Factory method for Fragment creation.

## Implementation Risks
*   **Class Loading**: Relies on finding the class by name.
