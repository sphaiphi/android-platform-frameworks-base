# DifferentialPrivacyEncoder - Reverse Engineering Documentation

## Executive Summary
`DifferentialPrivacyEncoder` is the primary interface for converting privacy-sensitive data into privacy-protected reports using differential privacy (DP) techniques. It supports encoding various data types like strings, booleans, and bit arrays. The interface is designed to be one-way; by design, there is no corresponding decoder within the Android framework.

## Architecture Overview
- **Pattern**: Encoder / Strategy Interface.
- **Role**: Provides a unified API for applying noise and randomization to data before reporting it.
- **Dependencies**: `DifferentialPrivacyConfig`.

## Detailed Functionality
The interface defines methods for encoding different primitives:
1.  **String Encoding**: Applies DP to a raw string.
2.  **Boolean Encoding**: Applies DP to a boolean value.
3.  **Bit Encoding**: Applies DP to a raw byte array.

### Core Concepts
- **PRR (Permanent Randomized Response)**: Used to create memoized "noisy" answers that are reused to prevent privacy leakage through repeated reports.
- **Test Mode**: Includes a check (`isInsecureEncoderForTest`) to identify if the encoder is using insecure/deterministic randomization, which is strictly for verification and must never be used for real user data.

## API Reference
- `encodeString(String original)`: Encodes a string. May throw `UnsupportedOperationException`.
- `encodeBoolean(boolean original)`: Encodes a boolean.
- `encodeBits(byte[] original)`: Encodes a sequence of bits.
- `getConfig()`: Returns the associated `DifferentialPrivacyConfig`.
- `isInsecureEncoderForTest()`: Returns `true` if the encoder is not securely randomized.

## Java-to-C++ Translation Guide
### Abstract Interface
Map to a C++ abstract class.

```cpp
class DifferentialPrivacyEncoder {
public:
    virtual ~DifferentialPrivacyEncoder() = default;
    virtual std::vector<uint8_t> encodeString(const std::string& original) = 0;
    virtual std::vector<uint8_t> encodeBoolean(bool original) = 0;
    virtual std::vector<uint8_t> encodeBits(const std::vector<uint8_t>& original) = 0;
    virtual const DifferentialPrivacyConfig& getConfig() const = 0;
    virtual bool isInsecureEncoderForTest() const = 0;
};
```

### Error Handling
Java throws `UnsupportedOperationException` for unsupported methods. In C++, use `std::expected` or throw a runtime exception if the implementation strictly violates the interface contract.

## Implementation Risks
- **Randomization Security**: The C++ implementation must use a cryptographically secure PRNG (like `std::random_device` or NDK's `arc4random`) unless in test mode.
- **Algorithmic Complexity**: Different algorithms (RAPPOR vs Longitudinal) have very specific mathematical requirements for noise injection.
- **One-Way Design**: Ensure that no "decoding" logic is accidentally exposed or possible through the implementation details.
