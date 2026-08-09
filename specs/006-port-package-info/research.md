# Research: port-package-info

This document consolidates research findings for the `port-package-info` feature, resolving technical unknowns and defining best practices for implementation.

## 1. Technical Context Research

### Performance Requirements
- **Metric**: Primary concern is build-time impact.
- **Requirement**: The tool must be highly efficient during incremental builds.
- **Recommendation**: Implement dependency tracking (e.g., using checksums of Java files) so headers are only regenerated when necessary. Use a high-performance language (C++ or Rust) for the tool itself.

### Annotation and Comment Porting
- **Documentation**: `package-info.java` comments should be ported as Doxygen-style comment blocks (`/** ... */`) in C++ headers to ensure IDE compatibility.
- **Annotations**:
  - Informational annotations (e.g., `@Deprecated`) should be converted to C++ comments (e.g., `// @Deprecated`).
  - Performance-critical annotations (e.g., `@FastNative`) should be converted to descriptive comments/warnings to alert developers of threading/GC constraints.

### C++23 and GoogleTest in NDK
- **C++23**: Use feature detection to ensure compatibility with the specific `libc++` version provided by the NDK. Explicitly set `CMAKE_CXX_STANDARD 23`.
- **Testing**: Use GoogleTest with CMake's `FetchContent` for reliable, ABI-consistent builds across different Android architectures (arm64-v8a, x86_64).
- **Verification**: Tests must be run on device/emulator to account for ABI nuances.

## 2. Implementation Decisions

### Decision: Annotation Mapping Strategy
- **Decision**: All Java annotations will be converted to C++ comment lines starting with `// @<AnnotationName>`.
- **Rationale**: Ensures documentation parity without introducing runtime complexity or requiring non-standard C++ attributes.
- **Alternatives Considered**: Creating custom C++ attributes. Rejected because it would require compiler/toolchain modifications that are outside the project scope.

### Decision: Build System Integration
- **Decision**: Integrate via CMake custom command with dependency tracking.
- **Rationale**: This allows for seamless incremental builds and standardizes the workflow within the NDK/CMake ecosystem.

### Decision: Output Format
- **Decision**: Doxygen-compliant block comments for `package-info` content.
- **Rationale**: Maximizes utility for developers using IDEs (Android Studio, CLion) which parse Doxygen-style comments for documentation.
- **Alternatives Considered**: Standard C-style comments (`/* ... */`). Rejected because Doxygen-style (`/** ... */`) is standard for modern C++ documentation.

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

## 3. Open Questions

| Question | Context | Status |
|---|---|---|
| How to handle complex nested annotations? | The current scope is limited to simple annotations, but nested ones might require a more robust parser. | **RESOLVED** — Out of scope, flat emission |
| How to handle `@link` or `@see` tags in Javadoc? | These might not map directly to C++ documentation without specialized tools. | **RESOLVED** — Preserved verbatim, Doxygen supports them |
