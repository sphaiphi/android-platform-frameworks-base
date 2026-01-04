# AbstractSynthesisCallback - Reverse Engineering Documentation

## Executive Summary
`AbstractSynthesisCallback` is an internal base class for TTS synthesis callbacks. it extends the public `SynthesisCallback` interface and adds lifecycle controls (like `stop`) and versioning info (`mClientIsUsingV2`).

## Architecture Overview

### Versioning
- `mClientIsUsingV2`: Boolean flag indicating if the request originated from the V2 TTS interface. This affects error codes.

## Detailed Functionality

### Stop Logic
- `abstract void stop()`: Aborts the speech request. Must be thread-safe.
- `errorCodeOnStop()`: Returns `TextToSpeech.STOPPED` for V2 clients and `TextToSpeech.ERROR` for V1 clients.

## Java-to-C++ Translation Guide

### Mapping
- Inherit from `SynthesisCallback`.
- Provide `stop()` as a virtual method.
- Store the client version flag to determine status codes during aborts.
