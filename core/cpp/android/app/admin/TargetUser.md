# TargetUser - Reverse Engineering Documentation

## 1. Executive Summary
`TargetUser` is a final class that represents the specific user to whom a device policy applies. It is primarily used in callbacks to `PolicyUpdateReceiver` (specifically `onPolicySetResult` and `onPolicyChanged`) to inform administrators about which user a policy update or change pertains to. The class uses predefined integer constants to signify different user contexts, such as the local user, the parent user (for managed profiles), or a global policy.

## 2. Architecture Overview
`TargetUser` is a simple, immutable value object that wraps an integer user ID. Its architecture is minimalistic, focusing on clearly defining different user scopes for policy application.

### Design Patterns
- **Value Object**: Represents a single, immutable user context.
- **Enumeration (via Constants)**: Uses `public static final int` constants to define symbolic user IDs, along with corresponding `public static final TargetUser` instances for convenience.

## 3. Detailed Functionality

### Constants
The class defines several `public static final int` constants representing special user IDs:
- **`LOCAL_USER_ID` (-1)**: The user on which the admin is installed.
- **`PARENT_USER_ID` (-2)**: The parent profile of a managed profile.
- **`GLOBAL_USER_ID` (-3)**: A global policy affecting all users.
- **`UNKNOWN_USER_ID` (-3)**: An unknown user, typically for conflicting policies on other secondary users.

It also provides pre-instantiated `TargetUser` objects for these common cases:
- **`LOCAL_USER`**: A `TargetUser` instance for `LOCAL_USER_ID`.
- **`PARENT_USER`**: A `TargetUser` instance for `PARENT_USER_ID`.
- **`GLOBAL`**: A `TargetUser` instance for `GLOBAL_USER_ID`.
- **`UNKNOWN_USER`**: A `TargetUser` instance for `UNKNOWN_USER_ID`.

### `public TargetUser(int userId)`
- **Purpose**: The sole constructor for creating a `TargetUser` instance.
- **Algorithm**: Assigns the provided `userId` to the `mUserId` final member field.

### `equals(@Nullable Object o)`
- **Purpose**: Provides a value-based equality check.
- **Algorithm**: Returns `true` if and only if the other object is also a `TargetUser` and their `mUserId` fields are equal.

### `hashCode()`
- **Purpose**: Generates a hash code consistent with the `equals` method.
- **Algorithm**: Delegates hash code generation to `Objects.hash(mUserId)`.

## 4. Data Model
- **`mUserId`**: `private final int`
  - **Type**: `int`
  - **Description**: The integer ID of the target user.

## 5. Java-to-C++ Translation Guide
- **Class Structure**: A C++ equivalent would be a simple `class` or `struct` containing a private `int` member.
  ```cpp
  class TargetUser {
  public:
      static const int LOCAL_USER_ID = -1;
      // ... other static const ints

      static const TargetUser LOCAL_USER;
      // ... other static const TargetUser instances

      explicit TargetUser(int userId);
      // ... comparison and hashing operators
  private:
      int mUserId;
  };
  ```
- **Constants**: Java `public static final int` constants translate directly to C++ `static const int` or `constexpr int` members. The pre-instantiated `TargetUser` objects could be implemented as static `const` instances.
- **`equals()`/`hashCode()`**: Translate to `operator==` and a custom `std::hash` specialization or a member `hashCode()` method.

## 6. Implementation Risks & Key Considerations
- **Meaning of `userId`**: The special negative values (`-1`, `-2`, `-3`) are semantic identifiers. A C++ implementation should clearly document the meaning of these values.
- **No Parcelable**: This class itself is not `Parcelable`, implying its `userId` is extracted and passed as a primitive `int` across IPC boundaries, or it is only used internally after `PolicyUpdateReceiver` has deserialized the `Intent`.

## 7. Questions for C++ Team
1.  Is there a standard C++ idiom for representing these kinds of special user IDs (e.g., specific `enum class` values, or simply integer constants)?
2.  How will the global constant `TargetUser` instances be managed in C++ to ensure they are singletons (if that's the intention)?
3.  Will policy update callbacks in C++ use an equivalent `TargetUser` object, or just pass the raw integer user ID?
