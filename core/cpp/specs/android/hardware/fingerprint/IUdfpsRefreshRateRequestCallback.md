# IUdfpsRefreshRateRequestCallback - Reverse Engineering Documentation

## Executive Summary
`IUdfpsRefreshRateRequestCallback` is an AIDL interface to request display refresh rate changes for UDFPS operations (since UDFPS often requires specific refresh rates).

## API Reference
- `onRequestEnabled(int displayId)`
- `onRequestDisabled(int displayId)`
- `onAuthenticationPossible(...)`

## Java-to-C++ Translation Guide
- **Binder**: Generated C++ code. Used by UdfpsController to callback to DisplayManager or similar components.

