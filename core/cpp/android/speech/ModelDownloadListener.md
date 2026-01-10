# ModelDownloadListener - Reverse Engineering Documentation

## Executive Summary
`ModelDownloadListener` is an interface used to receive updates regarding the progress of downloading a speech recognition model. It allows the `RecognitionService` to communicate status updates back to the client application.

## API Reference

### Methods
- `void onProgress(int completedPercent)`: Called to report download progress (0-100).
- `void onSuccess()`: Called when the model download is complete or the model is already available.
- `void onScheduled()`: Called if the download has been scheduled but will not happen immediately.
- `void onError(int error)`: Called when an error occurs. The error code corresponds to `SpeechRecognizer` error constants.

## Java-to-C++ Translation Guide

### Type
- Map to an abstract base class (interface) in C++.

### Methods
- `virtual void onProgress(int32_t completed_percent) = 0;`
- `virtual void onSuccess() = 0;`
- `virtual void onScheduled() = 0;`
- `virtual void onError(int32_t error) = 0;`

### Usage
- Used as a callback mechanism. In a binder context, this would likely correspond to `IModelDownloadListener` (AIDL). The C++ implementation would stub/proxy this interface.
