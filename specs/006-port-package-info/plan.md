# Implementation Plan: port-package-info

**Branch**: `main` | **Date**: 2026-07-28 | **Spec**: /home/roto/git/android-platform-frameworks-base/specs/006-port-package-info/spec.md

**Input**: Feature specification from `/home/roto/git/android-platform-frameworks-base/specs/006-port-package-info/spec.md`

## Summary

This feature ports the Java `PackageInfo` class (`core/java/android/content/pm/PackageInfo.java`) and package-level documentation (`package-info.java`) to C++. It consists of two deliverables:

1. **C++ API headers** — a `PackageInfo` class in `include/android/content/pm/` mirroring the Java API with C++23 idioms (strong types, `std::span`, `std::expected`, RAII).
2. **Package-info documentation** — generated Doxygen-style comment blocks from `package-info.java` files, preserving annotations as `// @<AnnotationName>` markers.

## Technical Context

**Language/Version**: C++23
**Primary Dependencies**: Android NDK r29+, GoogleTest
**Storage**: N/A (header-only + generated documentation)
**Testing**: GoogleTest (unit), Android CTS (compliance)
**Target Platform**: Android (NDK) — arm64-v8a, x86_64
**Project Type**: Library

**Performance Goals**:
- Header generation: ≤500ms per `package-info.java` file on a standard build machine (8-core CPU, 16GB RAM, SSD, Linux x86_64).
- Runtime: Zero-cost abstraction — the `PackageInfo` C++ class must have no measurable overhead vs. equivalent raw struct access.

**Constraints**:
- Must use C++23 features available in NDK r29 `libc++`.
- No new external dependencies beyond NDK and GoogleTest.
- Generated headers must compile with `-Wall -Werror -Wextra` on clang 18+.
- Java sources in `core/java/` are read-only reference — never built or executed.

**Scale/Scope**:
- Port the complete public API of `PackageInfo.java` (42 public fields, 8 static constants, 11 public methods).
- Handle all `package-info.java` files in `core/java/android/` (currently 2 found: `android/audio/policy/configuration/V7_0/` and `com/android/internal/`).
- Support incremental regeneration via CMake dependency tracking.

## Constitution Check

*GATE: Must pass before Phase 0 research. Re-check after Phase 1 design.*

- [x] **Principle I — Safety-First**: All generated code and new components MUST use modern C++23 idioms, RAII, smart pointers, and `std::expected`/`std::optional` for error handling.
  - `enum class` for all flag constants (e.g., `InstallLocation`, `RequestedPermissionFlag`).
  - `std::span<const char8_t>` for string arrays instead of raw pointers.
  - `std::optional<T>` for nullable fields (e.g., `versionName`, `sharedUserId`).
  - `std::expected<T, E>` for error paths in parsing/generation.
- [x] **Principle II — Zero-Cost Abstractions**: The `PackageInfo` struct uses static layout; no virtual dispatch, no heap allocation for fixed fields.
- [x] **Principle III — TDD**: All functionality verified via GoogleTest with >80% coverage.
- [x] **Principle IV — Spec as Source of Truth**: All implementation tasks tracked in `tasks.md`.
- [x] **Principle V — Tech Stack Deliberation**: No new external dependencies beyond NDK and GoogleTest.

## Project Structure

### Documentation (this feature)

```text
specs/006-port-package-info/
├── plan.md              # This file
├── research.md          # Phase 0 output
├── data-model.md        # Phase 1 output
├── quickstart.md        # Phase 1 output
├── contracts/           # Phase 1 output
│   └── package-info-header.md  # Generated header contract
└── tasks.md             # Phase 2 output
```

### Source Code (repository root)

```text
core/cpp/
├── include/android/
│   └── content/pm/
│       └── package_info.h       # C++ PackageInfo class header
├── src/android/
│   └── content/pm/
│       └── package_info.cpp     # Implementation (if any)
├── tools/
│   └── package_info_generator/  # Header generation tool
│       ├── main.cpp             # CLI entry point
│       ├── parser.cpp           # Java source parser
│       └── emitter.cpp          # C++ header emitter
├── tests/
│   └── package_info_test.cpp    # GoogleTest unit tests
├── CMakeLists.txt
└── Android.mk
```

**Structure Decision**: The C++ `PackageInfo` class goes in `include/android/content/pm/` mirroring the Java package namespace. The generation tool lives in `core/cpp/tools/` as a host-side utility.

## Phase 0: Research Findings (Resolved)

### Decision: Annotation Mapping Strategy
- **Decision**: All Java annotations converted to C++ comment lines: `// @<AnnotationName>`.
- **Rationale**: Documentation parity without runtime complexity or non-standard C++ attributes.
- **Alternatives considered**: Custom C++ attributes (rejected — requires toolchain mods).

### Decision: Build System Integration
- **Decision**: CMake custom command with dependency tracking (input file timestamps).
- **Rationale**: Seamless incremental builds within NDK/CMake ecosystem.

### Decision: Output Format
- **Decision**: Doxygen-compliant block comments (`/** ... */`) for package-info content.
- **Rationale**: Maximizes IDE utility (Android Studio, CLion).

### Decision: Nested Annotations
- **Decision**: Out of scope for initial port. Nested annotations will be emitted as flat `// @<AnnotationName>` lines. A follow-up feature will handle nested annotation structures if needed.
- **Rationale**: No nested annotations found in current `package-info.java` files.

### Decision: @link/@see Javadoc Tags
- **Decision**: Preserve verbatim in generated Doxygen comments. Doxygen supports `@link` and `@see` natively.
- **Rationale**: No transformation needed — Doxygen handles these tags.

### Decision: Java Parser
- **Decision**: Use a lightweight regex-based parser targeting `package-info.java` structure (package declaration + javadoc block + annotations). Not a full Java parser.
- **Rationale**: `package-info.java` files have a constrained, predictable structure. A full parser (TreeSitter, JavaCC) is overkill.

### Decision: Error Exit Codes
- **Decision**: Exit code mapping:
  - `0` — Success
  - `1` — Malformed input file (parse error)
  - `2` — File not found
  - `3` — Permission error (read/write)
  - `4` — Internal tool error
- **Rationale**: Distinct codes allow build systems to differentiate failure modes.

### Decision: Partial Failure Behavior
- **Decision**: Tool continues processing remaining files on individual file failure, reports all errors at end, exits with code `1`.
- **Rationale**: Maximizes information for developer — one run surfaces all issues.

## Phase 1: Design

### Data Model

See `data-model.md` for entity definitions. Key mappings:

| Java Type | C++ Type | Rationale |
|-----------|----------|-----------|
| `String` | `std::string_view` / `std::optional<std::string_view>` | Zero-copy view, optional for nullable |
| `String[]` | `std::span<const std::string_view>` | Contiguous, zero-copy |
| `int` | `int32_t` | Fixed-width for ABI stability |
| `int[]` | `std::span<const int32_t>` | Contiguous, zero-copy |
| `long` | `int64_t` | Fixed-width for ABI stability |
| `boolean` | `bool` | Direct mapping |
| `@Deprecated` | `// @Deprecated` comment | Documentation marker |
| `@hide` | `// @hide` comment | SDK visibility marker |
| `@NonNull` | Non-optional type | Enforced by type system |
| `@Nullable` | `std::optional<T>` | Enforced by type system |

### Interface Contract

See `contracts/package-info-header.md` for the public header contract.

### Error Handling

- Parse errors return `std::expected<void, ParseError>` with categorized error type.
- File I/O errors return `std::expected<void, IoError>` with system error code.
- CLI exits with specific codes (see Decision above).

### Performance

- Generation: ≤500ms/file on reference hardware (8-core, 16GB, SSD, Linux x86_64).
- Runtime: Struct layout matches Java field order for potential FFI compatibility.
- Memory: No heap allocation in `PackageInfo` struct — all data is views or inlined.

## Complexity Tracking

| Violation | Why Needed | Simpler Alternative Rejected Because |
|-----------|------------|--------------------------------------|
| Regex-based parser | `package-info.java` has constrained structure | Full Java parser (TreeSitter) adds build dependency and complexity |
| CMake custom command | Must integrate with existing NDK build flow | Separate build script requires manual invocation |

## Post-Design Constitution Re-Check

- [x] **Principle I**: Types use `enum class`, `std::span`, `std::optional`, `std::expected`. No raw pointers or primitive obsession.
- [x] **Principle II**: `PackageInfo` is a flat struct with views — zero allocation, zero virtual dispatch.
- [x] **Principle III**: TDD with GoogleTest, >80% coverage target per module.
- [x] **Principle IV**: Tasks tracked in `tasks.md`, progress logged.
- [x] **Principle V**: No new dependencies — regex parser is stdlib-only, CMake is existing build system.
