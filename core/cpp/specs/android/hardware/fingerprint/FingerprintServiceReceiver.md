# FingerprintServiceReceiver - Reverse Engineering Documentation

## Executive Summary
`FingerprintServiceReceiver` is an abstract base class (adapter) extending `IFingerprintServiceReceiver.Stub` with empty default implementations.

## Architecture Overview
- **Type**: Abstract Callback Adapter.
- **Implements**: `IFingerprintServiceReceiver` (AIDL).

## Detailed Functionality
- No-op implementations for all callback methods (`onEnrollResult`, `onAcquired`, `onAuthenticationSucceeded`, etc.).

## Java-to-C++ Translation Guide
- **Inheritance**: Inherit from `BnFingerprintServiceReceiver`.
- **Usage**: Helper class to avoid implementing all virtual methods.

