# TransferSplashScreenViewStateItem - Reverse Engineering Documentation

## Executive Summary
`TransferSplashScreenViewStateItem` transfers the state of the splash screen (view and surface control) to the activity. This allows the activity to animate or control the splash screen exit.

## Architecture Overview
- **Inheritance**: Extends `ActivityTransactionItem`.
- **Role**: Splash screen handoff.
- **Package**: `android.app.servertransaction`

## Detailed Functionality

### `execute`
**Purpose**: Transfers state.
**Algorithm**:
1. `client.handleAttachSplashScreenView(r, mSplashScreenViewParcelable, mStartingWindowLeash)`.

## Data Model

### Fields
| Name | Type | Description |
| :--- | :--- | :--- |
| `mSplashScreenViewParcelable` | `SplashScreenViewParcelable` | The splash view data. |
| `mStartingWindowLeash` | `SurfaceControl` | The surface control for the window. |

### Serialization (Parcelable)
- Standard read/write.

## Java-to-C++ Translation Guide

### Data Structures
- `SplashScreenViewParcelable` -> C++ equivalent.
- `SurfaceControl` -> `android::view::SurfaceControl` (C++).

## Implementation Risks
- **Surface Control**: Handling `SurfaceControl` across Binder requires careful lifecycle management (release).
