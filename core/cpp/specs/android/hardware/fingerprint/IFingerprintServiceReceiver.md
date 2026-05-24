# IFingerprintServiceReceiver - Reverse Engineering Documentation

## Executive Summary
`IFingerprintServiceReceiver` is the callback interface for clients to receive results from `IFingerprintService`.

## Architecture Overview
- **Type**: AIDL Interface (oneway).

## API Reference
- `onEnrollResult`
- `onAcquired`
- `onAuthenticationSucceeded` / `onAuthenticationFailed`
- `onFingerprintDetected`
- `onError`
- `onRemoved`
- `onChallengeGenerated`
- `onUdfpsPointerDown` / `onUdfpsPointerUp` / `onUdfpsOverlayShown`

## Java-to-C++ Translation Guide
- **Stub**: Clients implement Stub (Bn).

