# GestureLibrary - Reverse Engineering Documentation

## Executive Summary
`GestureLibrary` is an abstract base class managing a `GestureStore`. It defines the contract for loading, saving, and manipulating gesture sets.

## Architecture Overview
- **Composition**: Owns a `GestureStore` instance.
- **Abstract Methods**: `save()` and `load()` must be implemented by subclasses to handle specific storage media.

## Detailed Functionality
- **Delegation**: Most methods (`addGesture`, `removeGesture`, `recognize`) simply forward the call to the internal `mStore`.
- **Configuration**: Allows setting sequence and orientation sensitivity types.

## Java-to-C++ Translation Guide
- **Pattern**: Base class with pure virtual functions for `save()` and `load()`.
- **Members**: Holds a pointer/reference to `GestureStore`.

## Source Reference
Defined in `GestureLibrary.java`.
