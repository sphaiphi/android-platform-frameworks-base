# BiometricSourceType - Reverse Engineering Documentation

## Executive Summary
`BiometricSourceType` is an enum that identifies the specific modality of a biometric source. It is Parcelable to allow passing across IPC boundaries.

## Detailed Functionality

### Enum Values
- `FINGERPRINT`
- `FACE`
- `IRIS`

### Parcelable Implementation
- Writes the enum name (String) to the parcel.
- Reads the string and uses `valueOf()` to reconstruct.

## Java-to-C++ Translation Guide
- **Enum**: `enum class BiometricSourceType`.
- **Serialization**: When parceling to C++, it might be more efficient to send an integer index rather than a string, but if the Java side sends strings, the C++ side must read strings. *Note*: Check if AIDL definitions use enum backing or string. The Java code here writes `name()`.

## Implementation Risks
- String-based parceling is brittle if enum names change (unlikely for core types).
