# AGENTS.md

## Project

C++23 reimplementation of Android framework APIs for NDK developers.

* `core/java/` is the authoritative behavioral reference.
* `core/cpp/specs/` contains supplementary reverse-engineering notes and implementation guidance. Specs do not override Java behavior.
* Coding standards and C++ requirements are defined in `/cpp-coding` skill with `/software-design` skill uses.

## Implementation Priority

When behavior is unclear, use the following precedence:

1. Existing behavior in `core/java/`
2. CTS expectations
3. Related files in `core/cpp/specs/`
4. New design decisions

## Build Systems

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

## References

* `core/cpp/specs/*` — supplementary implementation notes
* `cts/xUNIT.md` — GoogleTest methodology and assertion guidance
