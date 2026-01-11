# MethodDescriptorParser - Reverse Engineering Documentation

## Executive Summary
`MethodDescriptorParser` is a utility class designed to convert a `MethodDescriptor` (a parcelable representation of a Java method signature) back into a live `java.lang.reflect.Executable` (Method or Constructor) object using a specific `ClassLoader`. It handles primitive types, arrays, and standard object references.

## Architecture Overview
-   **Role**: Utility / Converter.
-   **Input**: `ClassLoader` (context for loading classes), `MethodDescriptor` (struct with class name, method name, parameter types).
-   **Output**: `java.lang.reflect.Executable` (Common superclass of `Method` and `Constructor`).

## Detailed Functionality

### `parseMethodDescriptor`
1.  **Class Loading**: Loads the target class using `classLoader.loadClass(descriptor.fullyQualifiedClassName)`.
2.  **Parameter Resolution**: Iterates through `fullyQualifiedParameters`:
    -   Handles array syntax (suffix `[]`).
    -   Maps primitive type names ("int", "boolean", etc.) to their `Type.class` equivalents (or `Type.class.arrayType()` if array).
    -   Loads object types via the class loader.
3.  **Method/Constructor Resolution**:
    -   If `methodName` is `<init>` AND the feature flag `executableMethodFileOffsetsV2` is enabled, it attempts to find a **Constructor** via `getDeclaredConstructor`.
    -   Otherwise, it attempts to find a **Method** via `getDeclaredMethod`.
4.  **Error Handling**: Throws `IllegalArgumentException` wrapping `ClassNotFoundException` or `NoSuchMethodException` if the descriptor does not match a valid member.

## Data Model
-   **MethodDescriptor**:
    -   `fullyQualifiedClassName`: String (e.g. "com.example.MyClass")
    -   `methodName`: String (e.g. "myMethod" or "<init>")
    -   `fullyQualifiedParameters`: String[] (e.g. ["int", "java.lang.String[]"])

## API Reference
-   `static Executable parseMethodDescriptor(ClassLoader, MethodDescriptor)`: The sole public method.

## Java-to-C++ Translation Guide
-   **Relevance**: This is a Java-side reflection helper. C++ code generally interacts with the *result* of this process (the `ExecutableMethodFileOffsets` returned by ART), or constructs the `MethodDescriptor` struct to send *to* Java.
-   **C++ Equivalent**:
    -   If the C++ side needs to perform similar lookups via JNI, it would use `FindClass`, `GetMethodID`.
    -   The parsing logic (handling "int", "boolean") maps to JNI signatures (`I`, `Z`, `Ljava/lang/String;`).

## Implementation Risks
-   **Security**: Loading arbitrary classes via `ClassLoader` based on IPC input can be risky if not sandboxed.
-   **Reflection Overhead**: This is a heavy operation; repeated calls should be cached if performance matters.
-   **Flag Dependency**: The `<init>` support relies on `com.android.art.flags.Flags.executableMethodFileOffsetsV2()`.
