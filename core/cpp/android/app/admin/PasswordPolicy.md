# PasswordPolicy - Reverse Engineering Documentation

## 1. Executive Summary
`PasswordPolicy` is a hidden (`@hide`) class that encapsulates the various parameters defining a password quality policy, such as minimum length, required character types (letters, uppercase, lowercase, numeric, symbols), and overall quality level. Its primary function is to translate these policy settings into a `PasswordMetrics` object, which is then used by the system to evaluate the strength and compliance of a user's chosen password.

## 2. Architecture Overview
`PasswordPolicy` acts as a data container for password requirements. It's a simple, mutable object whose fields directly correspond to different aspects of password complexity. Its core logic is to generate a `PasswordMetrics` object that represents the *minimum* requirements a password must meet according to this policy.

### Design Patterns
- **Data Transfer Object (DTO)**: Primarily holds data related to a password policy.
- **Factory Method (Implicit)**: The `getMinMetrics()` method acts as a factory, constructing and returning a `PasswordMetrics` object based on the current policy settings.

## 3. Detailed Functionality

### Constants
The class defines several `public static final int` constants for default minimums (e.g., `DEF_MINIMUM_LENGTH = 0`, `DEF_MINIMUM_LETTERS = 1`). These defaults are used when no specific value is provided for a policy attribute.

### Member Fields
The class contains several public member fields, directly accessible and mutable:
- `quality`: (`int`) Represents the overall password quality (e.g., `PASSWORD_QUALITY_ALPHABETIC`, `PASSWORD_QUALITY_NUMERIC_COMPLEX`).
- `length`: (`int`) Minimum password length.
- `letters`: (`int`) Minimum number of letters.
- `upperCase`: (`int`) Minimum number of uppercase letters.
- `lowerCase`: (`int`) Minimum number of lowercase letters.
- `numeric`: (`int`) Minimum number of numeric digits.
- `symbols`: (`int`) Minimum number of symbols.
- `nonLetter`: (`int`) Minimum number of non-letter characters.

### `getMinMetrics()`
- **Purpose**: Translates the `PasswordPolicy` settings into a `PasswordMetrics` object that defines the minimum requirements for a compliant password.
- **Algorithm**:
    1.  Initializes a `PasswordMetrics` object based on the `quality` field. This sets the base credential type (NONE, PATTERN, PIN, PASSWORD) and sometimes a default `seqLength`.
    2.  Depending on the `quality`, it sets various fields in the `PasswordMetrics` object:
        -   `PASSWORD_QUALITY_UNSPECIFIED`: Returns metrics for `CREDENTIAL_TYPE_NONE`.
        -   `PASSWORD_QUALITY_BIOMETRIC_WEAK` or `PASSWORD_QUALITY_SOMETHING`: Returns metrics for `CREDENTIAL_TYPE_PATTERN`.
        -   `PASSWORD_QUALITY_NUMERIC` or `PASSWORD_QUALITY_NUMERIC_COMPLEX`: Returns metrics for `CREDENTIAL_TYPE_PIN`, setting `length` and potentially `seqLength` (`PasswordMetrics.MAX_ALLOWED_SEQUENCE`).
        -   `PASSWORD_QUALITY_ALPHABETIC`: Returns metrics for `CREDENTIAL_TYPE_PASSWORD`, setting `length` and `nonNumeric`.
        -   `PASSWORD_QUALITY_ALPHANUMERIC`: Returns metrics for `CREDENTIAL_TYPE_PASSWORD`, setting `length`, `numeric`, and `nonNumeric`.
        -   `PASSWORD_QUALITY_COMPLEX`: Returns metrics for `CREDENTIAL_TYPE_PASSWORD`, setting all granular character type requirements (`numeric`, `letters`, `upperCase`, `lowerCase`, `nonLetter`, `symbols`) based on the `PasswordPolicy`'s corresponding fields.
    3.  Returns the constructed `PasswordMetrics` object.
- **C++ Implementation Guidance**: A C++ equivalent would be a member function that constructs and returns a `PasswordMetrics` object (or a `std::unique_ptr<PasswordMetrics>`). The logic for mapping policy `quality` to specific `PasswordMetrics` fields would be directly translatable.

## 4. Data Model
The class directly exposes its policy attributes as public member fields.
- **`quality`**: `int`
- **`length`**: `int`
- **`letters`**: `int`
- **`upperCase`**: `int`
- **`lowerCase`**: `int`
- **`numeric`**: `int`
- **`symbols`**: `int`
- **`nonLetter`**: `int`

## 5. Java-to-C++ Translation Guide
- **Class Structure**: A C++ equivalent would be a struct or class with public member variables matching the Java fields.
  ```cpp
  class PasswordPolicy {
  public:
      static const int DEF_MINIMUM_LENGTH = 0;
      // ... other constants

      int quality = PASSWORD_QUALITY_UNSPECIFIED;
      int length = DEF_MINIMUM_LENGTH;
      // ... other member variables

      PasswordMetrics getMinMetrics() const; // Equivalent to the Java method
  };
  ```
- **Constants**: Java's `static final int` constants translate directly to C++ `static const int` or `constexpr int` member variables.
- **`PasswordMetrics`**: The `PasswordMetrics` class would need to be translated first, as `PasswordPolicy` depends on it.
- **Type Mapping**: Java `int` maps to C++ `int` or `int32_t` for fixed-width guarantees.

## 6. Implementation Risks & Key Considerations
- **Mutability**: The public fields in Java allow external modification of the policy attributes. If the C++ version needs to guarantee immutability after creation, a builder pattern would be a more idiomatic C++ approach, making all fields `const` after construction.
- **Hidden API**: The Java class is `@hide`, indicating it's an internal API. The C++ translation should similarly be treated as an internal component.

## 7. Questions for C++ Team
1.  Is there an existing C++ class or structure used for defining password policies that this translation should integrate with or replace?
2.  Should the C++ equivalent of `PasswordPolicy` be mutable (with public fields/setters) or immutable (using a constructor or builder pattern to set all fields)?
3.  Are there specific integer types (e.g., `int32_t` vs. `int`) that should be preferred for policy parameters to ensure platform consistency?
