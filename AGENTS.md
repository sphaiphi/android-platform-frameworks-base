# AGENTS.md

## Project

C++23 reimplementation of Android framework APIs for NDK developers.

* `core/java/` is the authoritative behavioral reference.
* `core/cpp/specs/` contains supplementary reverse-engineering notes and implementation guidance. Specs do not override Java behavior.
* Coding standards and C++ requirements are defined in `cpp-coding` skill with `software-design` skill uses.

## Implementation Priority

When behavior is unclear, use the following precedence:

1. Existing behavior in `core/java/`
2. CTS expectations
3. Related files in `core/cpp/specs/`
4. New design decisions

## Build Systems

### Prerequisites

All compiler and build toolchains must come from `$ANDROID_NDK_HOME`:

```bash
export PATH="$ANDROID_NDK_HOME/toolchains/llvm/prebuilt/linux-x86_64/bin:$PATH"
```

NDK headers and libraries are sourced from:

```bash
export ANDROID_FRAMEWORK_NATIVE_HOME=$HOME/git/android_frameworks_native
```

CMake invocations should use the NDK-provided toolchain:

```bash
cmake -B build -S core/cpp \
  -DCMAKE_CXX_COMPILER=$ANDROID_NDK_HOME/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++ \
  -DCMAKE_C_COMPILER=$ANDROID_NDK_HOME/toolchains/llvm/prebuilt/linux-x86_64/bin/clang
```

### Host Build

```bash
cmake -B build -S core/cpp
cmake --build build

cd build && ctest --output-on-failure
cd build && ctest -R Intent_test --output-on-failure

# or
./tests/framework_tests --gtest_filter="IntentTest.*"
```

Host builds define `HOST_BUILD` and use mock binder headers from `include/android_mock/`.

### CTS

```bash
cmake -B build_cts -S cts/cpp/tests
cmake --build build_cts

cd build_cts && ./framework_cts_tests
```

### Android Device Build

```bash
cd core/cpp && ndk-build
```

## Repository Layout

```text
core/cpp/
├── include/android/      # Public API headers
├── src/android/          # Framework implementation
├── src/android_mock/     # Host-only mocks
├── aidl/android/         # Generated AIDL bindings
├── specs/android/        # Supplementary implementation specs
├── tests/                # GoogleTest unit tests
├── CMakeLists.txt
└── Android.mk

core/java/                # Authoritative reference implementation

cts/
├── cpp/tests/            # C++ CTS tests
└── java/tests/           # AOSP CTS references
```

## Agent Guidance

* Verify behavior against `core/java/` before implementing new functionality.
* Consult related files in `core/cpp/specs/` during design and implementation.
* Framework namespaces mirror Android SDK package structure.
* TDD (Red → Green → Refactor) is preferred.
* Run relevant unit tests before completing a change.
* Use CTS tests to validate framework compatibility when applicable.
* Code quality is enforced through compiler warnings and tests; no automated linting is configured.

## Best Practices

### Parcel Serialization (ABI-Critical)
- Parcel write/read order must match Java field order exactly — order matters for ABI compatibility
- `boolean` → `writeInt(0/1)` in Parcel, `readInt() != 0` on read
- Nullable `Parcelable` → write `1` then parcel object, or `0` to skip; read sentinel first
- `Parcelable[]` → `writeTypedArray`/`createTypedArray(CREATOR)`
- `String[]` → `writeString8Array`/`createString8Array` (length-prefixed)
- Use `HOST_BUILD` define to enable mock Parcel headers from `include/android_mock/`

### C++ Type Mapping for Android Types
- `String` (nullable) → `std::optional<std::string_view>`
- `String[]` (nullable) → `std::optional<std::span<const std::string_view>>`
- `Parcelable[]` (nullable) → `std::optional<std::span<const T>>`
- `boolean` → `bool`
- Owned strings → `std::string` (e.g., `apex_package_name_`)
- Non-owned strings → `std::string_view`

### Test Patterns for Framework Porting
- Use `static` strings in tests to ensure lifetime for `std::string_view` fields
- Test default construction values first (zero/nullopt/false)
- Test individual field access before complex operations
- Check targeted build targets first to avoid pre-existing linker errors masking real issues

### Common Pitfalls
- Namespace qualification: tools in nested namespaces need full qualification in `main()`
- CMake policy warnings (e.g., `DOWNLOAD_EXTRACT_TIMESTAMP`) are non-blocking but should be addressed
- Generator tool path conversion relies on specific directory structure — fragile for non-standard layouts

## References

* `core/cpp/specs/*` — supplementary implementation notes
* `cts/xUNIT.md` — GoogleTest methodology and assertion guidance

<!-- SPECKIT START -->
For implementation plans, data models, contracts, and task breakdowns:
- Feature 006 (port-package-info): specs/006-port-package-info/plan.md
<!-- SPECKIT END -->
