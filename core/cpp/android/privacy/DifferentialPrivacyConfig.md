# DifferentialPrivacyConfig - Reverse Engineering Documentation

## Executive Summary
`DifferentialPrivacyConfig` is an interface that defines the configuration for differential privacy algorithms. It serves as a base for specific algorithm configurations, such as RAPPOR or Longitudinal Reporting, providing a common way to identify the underlying algorithm being used.

## Architecture Overview
- **Pattern**: Strategy / Configuration Interface.
- **Role**: Provides metadata about the differential privacy algorithm.
- **Implementations**: `RapporConfig`, `LongitudinalReportingConfig`.

## Detailed Functionality
The interface mandates a single method to retrieve the algorithm name. This name is used by encoders to ensure they are using the correct configuration type and for logging/diagnostic purposes.

## API Reference
### `getAlgorithm()`
- **Purpose**: Returns the string identifier of the differential privacy algorithm.
- **Return Type**: `String`.

## Java-to-C++ Translation Guide
### Interface Mapping
In C++, this can be represented as a pure virtual base class or a simple struct if no polymorphism is required. Given the usage, a pure virtual class is appropriate.

```cpp
class DifferentialPrivacyConfig {
public:
    virtual ~DifferentialPrivacyConfig() = default;
    virtual std::string getAlgorithm() const = 0;
};
```

## Implementation Risks
- **Extensibility**: When adding new algorithms, ensure the string returned by `getAlgorithm()` is unique across the system to avoid configuration mismatches.
