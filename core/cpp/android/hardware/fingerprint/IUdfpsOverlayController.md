# IUdfpsOverlayController - Reverse Engineering Documentation

## Executive Summary
`IUdfpsOverlayController` is an AIDL interface for interacting with the UDFPS (Under-Display Fingerprint Sensor) overlay (SystemUI).

## API Reference
- `showUdfpsOverlay(...)`
- `hideUdfpsOverlay(...)`
- `onAcquired(...)`
- `onEnrollmentProgress(...)`
- `onEnrollmentHelp(...)`
- `setDebugMessage(...)`

## Java-to-C++ Translation Guide
- **Binder**: Generated C++ code. System Server calls this to control the UI overlay.

