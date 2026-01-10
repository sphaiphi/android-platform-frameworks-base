# UndoManager - Reverse Engineering Documentation

## Executive Summary
`UndoManager` manages the undo/redo stack for an application or document. It groups `UndoOperation`s into `UndoState`s. It supports merging operations and labeled states.

## Architecture Overview
- **Structure:** Maintains two stacks: `mUndos` and `mRedos` (ArrayList of `UndoState`).
- **Owner Tracking:** `mOwners` map tracks `UndoOwner` objects by tag.

## Detailed Functionality

### `beginUpdate(CharSequence label)`
**Purpose**: Starts a composite operation.
**Algorithm**: Increments `mUpdateCount`. Creates `mWorking` state if needed.

### `addOperation(UndoOperation op, int mergeMode)`
**Purpose**: Adds an operation to the current working state.
**Algorithm**: Checks for merge opportunities with the top state if not currently updating.

### `commitState(UndoOwner owner)`
**Purpose**: Commits the current working state to the undo stack.

### `undo(UndoOwner[] owners, int count)`
**Purpose**: Performs undo.
**Algorithm**:
1. Finds the most recent state matching the owners.
2. Pops it from `mUndos`.
3. Calls `state.undo()`.
4. Pushes it to `mRedos`.

### `redo(UndoOwner[] owners, int count)`
**Purpose**: Performs redo.
**Algorithm**: Similar to undo, but moves from `mRedos` to `mUndos`.

## Data Model
- `mUndos`: `ArrayList<UndoState>`.
- `mRedos`: `ArrayList<UndoState>`.
- `mOwners`: `ArrayMap<String, UndoOwner>`.
- `mWorking`: `UndoState` (Current being built).

## Inner Classes
- `UndoState`: Represents one undoable step (commit). Contains a list of `UndoOperation`s.

## API Reference
- `public void beginUpdate(CharSequence label)`
- `public void endUpdate()`
- `public void addOperation(UndoOperation<?> op, int mergeMode)`
- `public int undo(UndoOwner[] owners, int count)`
- `public int redo(UndoOwner[] owners, int count)`

## Java-to-C++ Translation Guide
- **Generics**: `UndoOperation` uses generics.
- **Parcelable**: Supports saving state to Parcel.

## Implementation Risks
- **State Integrity**: Managing the undo/redo stacks correctly during merges and partial undos.