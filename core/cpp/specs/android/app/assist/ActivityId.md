# ActivityId - Reverse Engineering Documentation

## Executive Summary
`ActivityId` is a system identifier class used to uniquely reference a specific instance of an `Activity`. It encapsulates the `TaskId` (stack ID) and an `IBinder` token representing the activity. This is primarily used by system services (like `ContentCaptureService` or `UiTranslationManager`) to target specific activities for operations.

## Architecture Overview
- **Type**: Final Parcelable Class.
- **Role**: Identifier / Key.
- **Relationships**:
  - Part of `ContentCaptureContext`.
  - Used in system service IPC calls.

## Detailed Functionality

### Core Logic
- **Storage**: Holds an `int` Task ID and an `@Nullable IBinder` Activity Token.
- **Immutability**: The class is marked `@Immutable`, and all fields are `final`.

## Data Model

| Field Name | Java Type | C++ Equivalent Type | Description |
| :--- | :--- | :--- | :--- |
| `mTaskId` | `int` | `int32_t` | The ID of the task stack containing the activity. |
| `mActivityId` | `IBinder` | `sp<IBinder>` | The Binder token identifying the activity record. |

## API Reference

### Getters
- `getTaskId()`: Returns `int`.
- `getToken()`: Returns `IBinder` (nullable).

### Parcelable
- `writeToParcel`: Writes task ID then strong binder.
- `createFromParcel`: Reads task ID then strong binder.

### Object Methods
- `equals`/`hashCode`: Standard implementation based on both fields.
- `toString`: Debug string format.

## Java-to-C++ Translation Guide

### Binder Handling
- Java: `readStrongBinder()` / `writeStrongBinder()`.
- C++ (Binder): `readStrongBinder(&sp<IBinder>)` / `writeStrongBinder(sp<IBinder>)`.

## Test Cases & Validation
- **Serialization**: Verify parceling preserves both ID and Binder reference.
- **Equality**: Two `ActivityId`s with same TaskID and same Binder object must be equal.

## Implementation Risks
- **Binder Lifetime**: Ensure the `sp<IBinder>` is managed correctly in C++ to avoid leaks or premature destruction, though usually it's just a handle held by the system.
