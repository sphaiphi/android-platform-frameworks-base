# BackAnimationAdapter - Reverse Engineering Documentation

## Executive Summary
`BackAnimationAdapter` is a Parcelable class that encapsulates the logic and capabilities required to run a remote back navigation animation. It holds a reference to an `IBackAnimationRunner` (binder interface) and a list of supported animation types.

## Architecture Overview
*   **Package**: `android.window`
*   **Type**: `class` implements `Parcelable`
*   **Role**: Adapter/DTO to pass back animation runners to the system.
*   **Dependencies**:
    *   `IBackAnimationRunner` (AIDL interface)
    *   `BackNavigationInfo` (for `BackTargetType`)

## Detailed Functionality

### `isAnimatable(@BackTargetType int backType)`
**Purpose**: Checks if a specific back navigation type is supported by this adapter.
**Algorithm**:
1.  Checks if `mSupportedAnimators` array is null.
2.  Iterates through `mSupportedAnimators`.
3.  Returns `true` if `backType` matches any entry, `false` otherwise.

### `updateSupportedAnimators(@NonNull ArrayList<Integer> animators)`
**Purpose**: Updates the list of supported animation types.
**Algorithm**:
1.  Allocates a new `int[]` of the size of the input list.
2.  Copies values from the ArrayList to the primitive array (in reverse order in the source code loop, though order shouldn't strictly matter for set membership).

## Data Model

| Field | Type | Description |
| :--- | :--- | :--- |
| `mRunner` | `IBackAnimationRunner` | Binder interface to control the animation start/cancel. |
| `mSupportedAnimators` | `int[]` | Array of integer constants representing supported `BackTargetType`s. |

## API Reference

*   `BackAnimationAdapter(IBackAnimationRunner runner)`: Constructor.
*   `getRunner()`: Returns the binder interface.
*   `updateSupportedAnimators(ArrayList<Integer>)`: Updates supported types.
*   `isAnimatable(int backType)`: Checks support.

## Java-to-C++ Translation Guide

### Data Types
*   `IBackAnimationRunner` -> `sp<IBackAnimationRunner>` (Strong pointer to Binder interface).
*   `int[]` -> `std::vector<int>` or `std::array` (if fixed max size, though vector is safer).

### Serialization
*   **Write**:
    1.  `dest.writeStrongInterface(mRunner)`
    2.  `dest.writeInt(mSupportedAnimators.length)`
    3.  `dest.writeIntArray(mSupportedAnimators)`
*   **Read**:
    1.  `mRunner = IBackAnimationRunner.Stub.asInterface(in.readStrongBinder())`
    2.  Read length.
    3.  Read int array.

## Implementation Risks
*   **Binder Lifecycle**: Ensure the `IBackAnimationRunner` is kept alive as long as the adapter is valid in C++.
*   **Concurrency**: Access to `mSupportedAnimators` isn't synchronized in Java; verify if C++ usage implies multi-threaded access.
