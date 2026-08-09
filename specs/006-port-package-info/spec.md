# Feature Specification: port-package-info

**Feature Branch**: `[branch-placeholder]`

**Created**: 2026-07-28

**Status**: Draft

**Input**: User description: "port package-info from java to c++"

## Clarifications

### Session 2025-05-14

- Q: Source Content of `PackageInfo`? → A: Annotations only
- Q: Porting scope? → A: Port the complete set of methods and data members found in the Java PackageInfo class.
- Q: Feature Goal? → A: Port the android.content.pm.PackageInfo data class to C++.

## User Scenarios & Testing *(mandatory)*

### User Story 1 - Access Package Metadata in C++ (Priority: P1)

NDK developers can access critical package information (e.g., package name, version code) using a C++ representation of `PackageInfo` that matches the Java API.

**Why this priority**: Fundamental requirement for any PM-related framework interaction.

**Independent Test**: Instantiate a `PackageInfo` object in C++ and verify that fields like `packageName` and `versionCode` are accessible and correctly typed.

**Acceptance Scenarios**:

1. **Given** a `PackageInfo` object is populated, **When** accessing the `packageName`, **Then** the correct `std::string` (or equivalent) is returned.
2. **Given** a `PackageInfo` object is populated, **When** calling `getLongVersionCode()`, **Then** the resulting `int64_t` matches the combined major/minor version codes.

---

## Requirements *(mandatory)*

### Functional Requirements

- **FR-001**: System MUST provide a C++ class `android::content::pm::PackageInfo` that mirrors the fields of `android.content.pm.PackageInfo`.
- **FR-001a (Ownership)**: The C++ class MUST use non-owning views (`std::string_view`, `std::span`) for fields provided by the framework's internal memory buffers to ensure zero-cost access.
- **FR-002**: System MUST implement `getLongVersionCode()` and `setLongVersionCode()` using the following logic:
  - `getLongVersionCode() = ((long)versionCodeMajor << 32) | ((long)versionCode & 0xFFFFFFFFL)`
  - `versionCodeMajor = (int)(longVersionCode >> 32)`
  - `versionCode = (int)longVersionCode`
- **FR-003**: All Java `@NonNull` fields MUST be represented as non-optional types (e.g., `std::string_view` instead of `std::optional<std::string_view>`).
- **FR-004**: All Java `@Nullable` fields MUST be represented as `std::optional`.
- **FR-005**: System MUST implement `Parcelable` equivalent for C++:
  - **Serialization**: Fields MUST be written to the `Parcel` in the exact order they appear in the Java `writeToParcel` method.
  - **Deserialization**: Fields MUST be read from the `Parcel` in the same order.
  - **Version Tolerance**: If the `Parcel` contains more fields than the C++ class supports (newer version), the remaining bytes MUST be skipped.
- **FR-005a (Nullability)**: During deserialization, if a field marked `@NonNull` in the spec is missing or null in the `Parcel`, the system MUST throw a `runtime_error` or return a `std::expected` error to prevent corrupted state.
- **FR-006**: System MUST handle deprecated fields (e.g., `versionCode`) by marking them with `[[deprecated]]`.

### Key Entities *(include if feature involves data)*

- **PackageInfo**: A data structure containing comprehensive information about an installed Android package, including name, versioning, and permissions.

## Success Criteria *(mandatory)*

### Measurable Outcomes

- **SC-001**: C++ `PackageInfo` class contains all public members defined in `android.content.pm.PackageInfo`.
- **SC-002**: `getLongVersionCode` returns values identical to Java for all test cases.
- **SC-003**: Memory layout is optimized for C++23 while maintaining API compatibility.
- **SC-004**: Serialization/Deserialization tests pass with 100% data integrity.

## Assumptions

- The C++ implementation will reside in the `android::content::pm` namespace.
- `Parcelable` functionality will be provided by the existing `android_mock` or framework binder infrastructure.
- C++23 standards are used throughout.
