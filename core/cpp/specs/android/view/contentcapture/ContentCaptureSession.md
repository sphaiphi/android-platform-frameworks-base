# ContentCaptureSession - Reverse Engineering Documentation

## Executive Summary
Abstract base class for a content capture session. It handles the state machine (active, disabled, etc.), child sessions, and buffering/flushing of events.

## Architecture
*   **State Machine**: `UNKNOWN_STATE`, `STATE_ACTIVE`, `STATE_DISABLED`, etc.
*   **Buffering**: `flush()` method abstract, implemented by `MainContentCaptureSession`.
*   **Hierarchy**: `mChildren` list.
*   **View API**: `notifyViewAppeared`, `notifyViewTextChanged`, etc. create events and delegate to internal abstract methods.

## Key Methods
*   **`notifyViewAppeared`**: Validates node and calls `internalNotifyViewAppeared`.
*   **`newViewStructure`**: Factory for `ViewStructureImpl` (wrapping `ViewNode`).

## Java-to-C++ Translation Guide
*   **Abstract Base Class**: C++ inheritance.
*   **ID Generation**: `SecureRandom` for session IDs.
