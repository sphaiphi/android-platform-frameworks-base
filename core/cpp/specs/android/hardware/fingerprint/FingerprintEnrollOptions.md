# FingerprintEnrollOptions - Reverse Engineering Documentation

## Executive Summary
`FingerprintEnrollOptions` is a configuration class for fingerprint enrollment requests. Currently holds the enrollment reason. It is Parcelable.

## Architecture Overview
- **Type**: Data Class / Parcelable.
- **Generation**: Generated via `codegen`.

## Detailed Functionality
- **Fields**:
    - `mEnrollReason` (`int`): Reason for enrollment.

## Constants (EnrollReason)
- `ENROLL_REASON_UNKNOWN` (0)
- `ENROLL_REASON_RE_ENROLL_NOTIFICATION` (1)
- `ENROLL_REASON_SETTINGS` (2)
- `ENROLL_REASON_SUW` (3)

## Java-to-C++ Translation Guide
- **Class**: C++ struct/class.
- **Enum**: Map constants to C++ enum.
- **Parcelable**: Read/Write single integer.

## API Reference
- `getEnrollReason()`
- `Builder` class.

