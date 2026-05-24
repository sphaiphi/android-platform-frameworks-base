# RecognitionSupportCallback - Reverse Engineering Documentation

## Executive Summary
`RecognitionSupportCallback` is a client-side interface used to receive the results of a `SpeechRecognizer.checkRecognitionSupport()` call. It provides the `RecognitionSupport` object or an error code.

## API Reference

### Methods
- `void onSupportResult(@NonNull RecognitionSupport recognitionSupport)`: Called when the support check is successful.
- `void onError(int error)`: Called when the check fails. Error codes are from `SpeechRecognizer`.

## Java-to-C++ Translation Guide

### Type
- Abstract base class or `std::function` callback in C++.

### Methods
- `virtual void onSupportResult(const RecognitionSupport& support) = 0;`
- `virtual void onError(int32_t error) = 0;`

### Context
- Typically wraps an underlying Binder callback (`IRecognitionSupportCallback`).
