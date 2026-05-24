# PasswordMetrics - Reverse Engineering Documentation

## 1. Executive Summary
`PasswordMetrics` is a final, `Parcelable` class that quantifies the characteristics of a password or credential, such as its type (NONE, PATTERN, PIN, PASSWORD), length, and the count of various character categories (letters, uppercase, numeric, symbols). It also assesses the maximum length of character sequences within the password. This class is fundamental to the Android device administration framework for evaluating whether a given credential meets specified complexity requirements. It provides static utility methods for computing metrics from a `LockscreenCredential` and for validating password compliance against administrative policies.

## 2. Architecture Overview
`PasswordMetrics` is a data-centric class that represents a detailed analysis of a password's properties. It is designed to be immutable once computed (though its fields are public for direct access by internal components like `PasswordPolicy`). Its core functionality revolves around character analysis and sequence detection.

### Inheritance
- **`java.lang.Object`**: The root of the class hierarchy.
- **`android.os.Parcelable`**: Enables the object to be efficiently serialized and deserialized for IPC.

### Design Patterns
- **Value Object**: Represents a quantifiable snapshot of a password's strength.
- **Utility Class (Static Methods)**: Contains several static methods for computing metrics and performing validation, making it a functional component for password analysis.
- **Enumeration (via `IntDef`)**: Uses `@IntDef` for `CharacterCatagory` and `CredentialType` to provide type-safe constants.

## 3. Detailed Functionality

### Constants
- **`MAX_ALLOWED_SEQUENCE` (3)**: Defines the maximum allowed length for character sequences to be considered "complex".

### Member Fields (public)
- **`credType`**: (`int`, `@CredentialType`) Type of credential (NONE, PATTERN, PIN, PASSWORD).
- **`length`**: (`int`) Total length of the credential.
- **`letters`**: (`int`) Count of alphabetic characters.
- **`upperCase`**: (`int`) Count of uppercase letters.
- **`lowerCase`**: (`int`) Count of lowercase letters.
- **`numeric`**: (`int`) Count of numeric digits.
- **`symbols`**: (`int`) Count of symbols.
- **`nonLetter`**: (`int`) Count of non-alphabetic characters.
- **`nonNumeric`**: (`int`) Count of non-numeric characters.
- **`seqLength`**: (`int`) Maximum length of a sequential character series (e.g., "123" is length 3). Initialized to `Integer.MAX_VALUE` for the least restrictive.

### Constructors
- **`PasswordMetrics(int credType)`**: Initializes with a credential type.
- **`PasswordMetrics(int credType, int length, ..., int seqLength)`**: Full constructor.
- **`private PasswordMetrics(PasswordMetrics other)`**: Copy constructor.

### `sanitizeComplexityLevel(@PasswordComplexity int complexityLevel)` (static)
- **Purpose**: Ensures a password complexity level is one of the valid predefined values.
- **Algorithm**: Returns the input `complexityLevel` if valid; otherwise, defaults to `PASSWORD_COMPLEXITY_NONE` and logs a warning.

### `computeForCredential(LockscreenCredential credential)` (static)
- **Purpose**: Computes `PasswordMetrics` for a given `LockscreenCredential`.
- **Algorithm**:
    - If `credential` is a password or PIN, delegates to `computeForPasswordOrPin()`.
    - If a pattern, sets `credType` to `CREDENTIAL_TYPE_PATTERN` and `length` to the pattern size.
    - If none, sets `credType` to `CREDENTIAL_TYPE_NONE`.
    - Throws `IllegalArgumentException` for unknown types.

### `computeForPasswordOrPin(byte[] credential, boolean isPin)` (private static)
- **Purpose**: Analyzes character categories and sequences for password/PIN types.
- **Algorithm**: Iterates through credential bytes, categorizing each character and incrementing counters for `letters`, `upperCase`, `lowerCase`, etc. Calls `maxLengthSequence()` to determine sequential length.

### `maxLengthSequence(@NonNull byte[] bytes)` (static)
- **Purpose**: Determines the maximum length of monotonically increasing/decreasing or repeated character sequences within a byte array.
- **Algorithm**: Iterates through the input, identifying character categories (lower, upper, digit, symbol) and calculating the maximum contiguous sequence length. It handles repetitions and sequential ordering within a category.

### Character Categorization (`categoryChar`, `maxDiffCategory`)
- **Purpose**: Helper methods to categorize characters and define maximum differences for sequence detection.

### `merge(List<PasswordMetrics> metrics)` (static)
- **Purpose**: Combines multiple `PasswordMetrics` to find the weakest (least permissive) metrics that satisfies all of them.
- **Algorithm**: Initializes a `PasswordMetrics` of `CREDENTIAL_TYPE_NONE`, then iteratively calls `maxWith()` for each metric in the list.

### `maxWith(PasswordMetrics other)`
- **Purpose**: Modifies current metrics to be at least as strong as `other` metrics for each criterion.
- **Algorithm**: For each metric field (length, letters, etc.), it takes the `Math.max` of `this` and `other` values, effectively enforcing the stricter requirement. For `seqLength`, it takes `Math.min` as a smaller sequence length means stricter policy.

### `complexityLevelToMinQuality(int complexity)` (static)
- **Purpose**: Maps a complexity level to a minimum password quality.

### `ComplexityBucket` (private enum)
- **Purpose**: Defines an internal enum to represent requirements for different complexity levels (HIGH, MEDIUM, LOW, NONE). Each bucket knows if it allows sequences, its minimum length, and allowed credential types.

### `satisfiesBucket(ComplexityBucket bucket)` (private)
- **Purpose**: Checks if the current `PasswordMetrics` meets the requirements of a given `ComplexityBucket`.

### `determineComplexity()`
- **Purpose**: Determines the highest complexity level that the current password metrics satisfies.

### `validateCredential(...)` and `validatePasswordMetrics(...)` (static)
- **Purpose**: Core validation logic for checking a password/credential against administrative requirements.
- **Algorithm**:
    1.  `validateCredential` first checks for invalid characters, then computes `actualMetrics`.
    2.  `validatePasswordMetrics` compares `actualMetrics` against `adminMetrics` (admin policies) and `minComplexity` (requester's complexity).
    3.  It builds a list of `PasswordValidationError` for any unmet criteria, checking `credType`, length, and various character counts.
    4.  It calls `applyComplexity` to derive a combined minimum requirement, and `removeOverlapping` to optimize the requirements list.

### `removeOverlapping()` (private)
- **Purpose**: Optimizes policy requirements by removing redundant checks (ee.g., if total letters are sufficient due to uppercase/lowercase requirements, the `letters` requirement itself can be dropped).

### `applyComplexity(...)` (static)
- **Purpose**: Combines admin metrics with complexity level requirements to form a comprehensive minimum `PasswordMetrics`.

### `isNumericOnly(@NonNull String password)` (static)
- **Purpose**: Checks if a string contains only numeric digits.

## 4. Data Model
- **`credType`**: `public int`
- **`length`**: `public int`
- **`letters`**: `public int`
- **`upperCase`**: `public int`
- **`lowerCase`**: `public int`
- **`numeric`**: `public int`
- **`symbols`**: `public int`
- **`nonLetter`**: `public int`
- **`nonNumeric`**: `public int`
- **`seqLength`**: `public int`

## 5. Java-to-C++ Translation Guide
- **Class Structure**: A C++ equivalent would be a `struct` or `class` with public members mirroring the Java fields. Enums or `int` with clear constants would replace Java `IntDef` annotations.
  ```cpp
  struct PasswordMetrics {
      // ... constants
      CredentialType credType; // enum
      int length;
      // ... other fields

      static PasswordMetrics computeForCredential(const LockscreenCredential& credential);
      // ... other static and member functions
  };
  ```
- **Character Analysis**: The `categoryChar` and `maxLengthSequence` logic needs to be carefully ported to C++, respecting character encoding (e.g., UTF-8 vs. Java's internal char representation).
- **Enums**: Java `IntDef`s map well to C++ `enum class` for type safety.
- **`Parcelable`**: A custom C++ serialization/deserialization mechanism is needed. It would involve writing/reading all member fields in the exact same order as the Java `writeToParcel`.
- **Dependencies**: `LockscreenCredential` and `PasswordValidationError` would also need to be translated.

## 6. Implementation Risks & Key Considerations
- **Character Encoding**: The `maxLengthSequence` and `categoryChar` methods operate on `char` from `byte[]`. This implicitly assumes a single-byte character encoding (like ASCII or Latin-1) for common password characters. If credentials can contain multi-byte UTF-8 characters, the C++ implementation must handle this correctly to avoid incorrect length or category calculations.
- **Validation Logic**: The validation rules for password complexity are extensive and critical for security. The C++ implementation must replicate these rules exactly.
- **`TODO` Comments**: The presence of `TODO: move to PasswordPolicy` suggests that some methods (`sanitizeComplexityLevel`, `merge`, `maxWith`, `complexityLevelToMinQuality`, `satisfiesBucket`, `determineComplexity`, `validateCredential`, `validatePasswordMetrics`, `comparePasswordMetrics`, `removeOverlapping`, `applyComplexity`) might eventually be refactored into a `PasswordPolicy` class. The C++ design should anticipate this.

## 7. Questions for C++ Team
1.  What is the standard C++ library/approach for handling character categorization (alphabetic, numeric, symbol) that should be used to port `categoryChar`?
2.  How will `LockscreenCredential` and `PasswordValidationError` be represented in C++?
3.  Are there any specific Unicode considerations for password analysis in the C++ environment that might impact the `maxLengthSequence` logic?
