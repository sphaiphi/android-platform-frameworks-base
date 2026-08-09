# Quickstart Guide: port-package-info

This guide demonstrates how to use the `port-package-info` tool to generate C++ headers from Java `package-info.java` files.

## Prerequisites

- **Android NDK**: Installed and configured in your environment.
- **CMake**: Version 3.20 or higher.
- **Java JDK**: To run the parser (if not using a native implementation).
- **GoogleTest**: Required for running the validation tests.

## Usage

### 1. Generate C++ Headers

To port a package's information, run the generator tool from your project root. (Note: The exact command depends on the final implementation, e.g., a CMake target or a standalone binary).

```bash
# Example if integrated as a CMake target
cmake --build build --target port-package-info
```

### 2. Verify Generated Files

After running the tool, check the `core/cpp/include/android/` directory for the generated header files.

```bash
# Example check
ls core/cpp/include/android/*.h
```

### 3. Run Validation Tests

The following tests verify that the generated headers contain the correct comments and annotations.

```bash
cd build
ctest -R PackageInfoTests
```

## Expected Outcomes

- A `.h` file is created for the target package.
- The `.h` file contains a Doxygen-compliant block comment (`/** ... */`) matching the `package-info.java` documentation.
- Java annotations (like `@Deprecated`) are preserved as C++ comments (e.g., `// @Deprecated`).

## Troubleshooting

- **No headers generated**: Ensure the `package-info.java` file exists in the source directory and the generator is correctly configured in your `CMakeLists.txt`.
- **Test failures**: Check the `research.md` and `data-model.md` in the feature directory for details on the expected mapping rules.
