# SpeechRecognizerProxy - Reverse Engineering Documentation

## Executive Summary
`SpeechRecognizerProxy` is an internal wrapper for a `SpeechRecognizer` implementation. Its primary purpose is to manage the lifecycle of the recognizer and ensure that resources are properly released using `CloseGuard`.

## Architecture Overview

### Design Pattern: Proxy
- Extends `SpeechRecognizer`.
- Delegates all calls to an underlying `mDelegate` instance.

### Lifecycle Management
- **CloseGuard**: Uses `android.util.CloseGuard` to warn if the object is finalized without `destroy()` being called.
- **Finalizer**: Overrides `finalize()` to warn and call `destroy()`.
- **destroy()**: Closes the `CloseGuard` and calls `mDelegate.destroy()`.

## API Reference
- Delegates all standard `SpeechRecognizer` methods (`startListening`, `stopListening`, `cancel`, `setRecognitionListener`, etc.).

## Java-to-C++ Translation Guide

### Lifetime Safety
- In C++, use `std::unique_ptr` or `std::shared_ptr` for ownership.
- The `CloseGuard` pattern can be approximated using RAII (destructor) to ensure `destroy()` is called.
- If explicit `destroy()` is required by the API, the destructor should at least log an error if it wasn't called, or perform the cleanup itself.
