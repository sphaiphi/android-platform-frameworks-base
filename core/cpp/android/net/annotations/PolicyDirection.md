# PolicyDirection.java - Reverse Engineering Documentation

## Executive Summary
`PolicyDirection` is a custom annotation used within the Android networking stack to enforce type safety for IPsec traffic direction constants. It constrains integer values to those defined in `IpSecManager`.

## Architecture Overview
- **Type**: Typedef Annotation (`@IntDef`)
- **Package**: `android.net.annotations`
- **Visibility**: `@hide` (Internal System API)
- **Retention**: `RetentionPolicy.SOURCE` (Discarded by compiler, used for linting/IDE checks).

## Detailed Functionality
The annotation uses `@IntDef` to group valid integer constants for IPsec directions:
1.  **`IpSecManager.DIRECTION_IN`**: Indicates inbound traffic.
2.  **`IpSecManager.DIRECTION_OUT`**: Indicates outbound traffic.

By using this annotation on method parameters or return types, the build system (via Lint) can ensure that only these specific constants are passed, preventing logical errors from using arbitrary integers.

## Java-to-C++ Translation Guide

### Enum Mapping
In C++, this type-safety is naturally handled by an `enum class`.

```cpp
namespace android::net {

enum class PolicyDirection : int32_t {
    IN = 0,  // Value should match IpSecManager.DIRECTION_IN
    OUT = 1  // Value should match IpSecManager.DIRECTION_OUT
};

} // namespace android::net
```

### Considerations
-   Since this is a `SOURCE` retention annotation in Java, it doesn't exist at runtime. Its C++ equivalent is a first-class type (enum).
-   Ensure the integer values assigned to the C++ enum match the constants in the corresponding C++ implementation of `IpSecManager` (typically found in `libandroid_net` or similar native networking libraries).
