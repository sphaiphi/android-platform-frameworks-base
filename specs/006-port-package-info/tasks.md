---

description: "Task list for port-package-info feature"
---

# Tasks: port-package-info

**Input**: Design documents from `/specs/006-port-package-info/`

**Prerequisites**: plan.md, spec.md, data-model.md, contracts/package-info-header.md, research.md, quickstart.md

**Tests**: Test tasks included per Constitution Principle III (TDD non-negotiable).

**Organization**: Tasks are grouped by user story to enable independent implementation and testing.

## Format: `[ID] [P?] [Story] Description`

- **[P]**: Can run in parallel (different files, no dependencies)
- **[Story]**: Which user story this task belongs to (e.g., US1)
- Include exact file paths in descriptions

## Path Conventions

- **Source**: `core/cpp/include/android/`, `core/cpp/src/android/`
- **Tests**: `core/cpp/tests/`
- **Tools**: `core/cpp/tools/package_info_generator/`

---

## Phase 1: Setup (Shared Infrastructure)

**Purpose**: Project initialization and basic structure

- [X] T001 Create directory structure: `core/cpp/include/android/content/pm/`, `core/cpp/src/android/content/pm/`, `core/cpp/tools/package_info_generator/`
- [X] T002 Add `content/pm/` subdirectory targets to `core/cpp/include/android/CMakeLists.txt` for `package_info.h` header-only library
- [X] T003 Add `content/pm/` subdirectory target to `core/cpp/src/android/CMakeLists.txt` (create if missing) for `package_info.cpp`
- [X] T004 Register `tools/package_info_generator/` as a host-side CMake custom target in `core/cpp/CMakeLists.txt`
- [X] T005 Add `package_info_test.cpp` to `core/cpp/tests/CMakeLists.txt` test executable

---

## Phase 2: Foundational (Blocking Prerequisites)

**Purpose**: Core types and infrastructure that MUST be complete before PackageInfo implementation

**⚠️ CRITICAL**: No PackageInfo work can begin until this phase is complete

- [X] T006 [P] Define `enum class InstallLocation : int32_t` in `core/cpp/include/android/content/pm/package_info.h` with values UNSPECIFIED=-1, AUTO=0, INTERNAL_ONLY=1, PREFER_EXTERNAL=2
- [X] T007 [P] Define `enum class RequestedPermissionFlag : int32_t` in `core/cpp/include/android/content/pm/package_info.h` with values REQUIRED=0x00000001, GRANTED=0x00000002, IMPLICIT=0x00000004, NEVER_FOR_LOCATION=0x00010000
- [X] T008 Add forward declarations for all referenced types in `core/cpp/include/android/content/pm/package_info.h`: ApplicationInfo, ActivityInfo, ServiceInfo, ProviderInfo, InstrumentationInfo, PermissionInfo, ConfigurationInfo, FeatureInfo, FeatureGroupInfo, SigningInfo, Attribution, Signature
- [X] T009 Implement regex-based `package_info_generator` parser in `core/cpp/tools/package_info_generator/parser.cpp` — extracts package name, javadoc block, and annotations from `package-info.java` files
- [X] T010 Implement `package_info_generator` emitter in `core/cpp/tools/package_info_generator/emitter.cpp` — converts Java annotations to `// @<AnnotationName>` comment markers and generates Doxygen-compliant `/** ... */` blocks
- [X] T011 Implement `package_info_generator` CLI entry point in `core/cpp/tools/package_info_generator/main.cpp` — iterates `package-info.java` files, invokes parser+emitter, exits with codes 0/1/2/3/4
- [X] T012 [P] Create `core/cpp/src/android/content/pm/package_info.cpp` with empty implementation skeleton (default-constructors, method stubs)
- [X] T013 [P] Create `core/cpp/tests/package_info_test.cpp` with empty test fixture and `TEST_F(PackageInfoTest, Empty)` as a placeholder

**Checkpoint**: Foundation ready — PackageInfo implementation can now begin

---

## Phase 3: User Story 1 — Access Package Metadata in C++ (Priority: P1) 🎯 MVP

**Goal**: NDK developers can access critical package information (package name, version code, etc.) using a C++ `android::content::pm::PackageInfo` class that mirrors the Java API.

**Independent Test**: Instantiate a `PackageInfo` object in C++ and verify that fields like `package_name` and `version_code` are accessible and correctly typed. Call `long_version_code()` and `set_long_version_code()` and verify the version code composition logic matches the Java implementation.

### Tests for User Story 1

> **NOTE**: Write these tests FIRST, ensure they FAIL before implementation (Constitution Principle III).

- [X] T014 [P] [US1] Test: PackageInfo default construction initializes all fields to default/zero values — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T015 [P] Test: `package_name` field accepts and returns `std::string_view` correctly — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T016 [P] Test: `version_name` is `std::nullopt` by default and accepts a valid string — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T017 [P] Test: `shared_user_id` is `std::nullopt` by default — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T018 [P] Test: `split_names` and `split_revision_codes` accept `std::span<const T>` and return correct data — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T019 [P] Test: `gids`, `activities`, `receivers`, `services`, `providers`, `instrumentation`, `permissions`, `requested_permissions`, `requested_permissions_flags`, `attributions`, `signatures`, `config_preferences`, `req_features`, `feature_groups` are all `std::nullopt` by default — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T020 [P] Test: `install_location` defaults to `InstallLocation::INTERNAL_ONLY` — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T021 [P] Test: `is_stub`, `core_app`, `required_for_all_users`, `overlay_is_static`, `compile_sdk_version`, `is_apex`, `is_active_apex`, `overlay_priority` default to `false`/0 — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T022 [P] Test: `long_version_code()` returns correct 64-bit value from `version_code_major` (upper 32) and `version_code` (lower 32) — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T023 [P] Test: `set_long_version_code()` correctly splits a 64-bit value into `version_code_major` and `version_code` — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T024 [P] Test: `compose_long_version_code()` static method matches Java behavior for all edge cases (negative major, overflow) — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T025 [P] Test: `first_install_time` and `last_update_time` store and return `int64_t` correctly — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T026 [P] Test: `shared_user_label` stores and returns `int32_t` correctly — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T027 [P] Test: `application_info` accepts `std::optional<std::reference_wrapper<const ApplicationInfo>>` — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T028 [P] Test: `signing_info` accepts `std::optional<std::reference_wrapper<const SigningInfo>>` — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T029 [P] Test: `restricted_account_type`, `required_account_type`, `overlay_target`, `target_overlayable_name`, `overlay_category`, `compile_sdk_version_codename` are `std::optional<std::string_view>` — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T030 [P] Test: `archive_time_millis()` getter returns correct `int64_t` value — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T031 [P] Test: `set_archive_time_millis()` sets the internal field — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T032 [P] Test: `apex_package_name()` returns `std::optional<std::string_view>` — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T033 [P] Test: `set_apex_package_name()` sets the internal field — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T034 [P] Test: `is_overlay_package()` and `is_static_overlay_package()` return correct results based on internal state — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T035 [P] Test: `to_string()` produces a human-readable string representation of all fields — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T036 [P] Test: `describe_contents()` returns 0 — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T037 [P] Test: `write_to_parcel()` serializes all fields to a Parcel-like buffer — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T038 [P] Test: `PackageInfo(void& parcel)` constructor deserializes all fields from a Parcel-like buffer — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T039 [P] Test: Serialization round-trip preserves all field values with 100% data integrity — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T040 [P] Test: Static constants `REQUESTED_PERMISSION_REQUIRED`, `REQUESTED_PERMISSION_GRANTED`, `REQUESTED_PERMISSION_NEVER_FOR_LOCATION`, `REQUESTED_PERMISSION_IMPLICIT` have correct values — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T041 [P] Test: Static constants `INSTALL_LOCATION_UNSPECIFIED`, `INSTALL_LOCATION_AUTO`, `INSTALL_LOCATION_INTERNAL_ONLY`, `INSTALL_LOCATION_PREFER_EXTERNAL` have correct values — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T042 [P] Test: Deprecated fields (`version_code`, `signatures`) are marked with `[[deprecated]]` or `// @Deprecated` comment — `core/cpp/tests/package_info_test.cpp`
- [X] [US1] T043 [P] Test: `@hide` fields are annotated with `// @hide` comment in the header — `core/cpp/tests/package_info_test.cpp`

### Implementation for User Story 1

- [X] T044 [P] [US1] Write `#pragma once` header guard and all `#include` directives in `core/cpp/include/android/content/pm/package_info.h`
- [X] T045 [US1] Implement `enum class InstallLocation` and `enum class RequestedPermissionFlag` in `core/cpp/include/android/content/pm/package_info.h`
- [X] T046 [US1] Declare all forward-referenced types in `android::content::pm` namespace in `core/cpp/include/android/content/pm/package_info.h`
- [X] T047 [US1] Declare `class PackageInfo` with all 42 public fields in `core/cpp/include/android/content/pm/package_info.h` following the contract:
  - `std::string_view package_name`
  - `std::span<const std::string_view> split_names`
  - `int32_t version_code` (deprecated)
  - `int32_t version_code_major`
  - `std::optional<std::string_view> version_name`
  - `int32_t base_revision_code`
  - `std::span<const int32_t> split_revision_codes`
  - `std::optional<std::string_view> shared_user_id`
  - `int32_t shared_user_label`
  - `std::optional<std::reference_wrapper<const ApplicationInfo>> application_info`
  - `int64_t first_install_time`
  - `int64_t last_update_time`
  - `std::optional<std::span<const int32_t>> gids`
  - `std::optional<std::span<const ActivityInfo>> activities`
  - `std::optional<std::span<const ActivityInfo>> receivers`
  - `std::optional<std::span<const ServiceInfo>> services`
  - `std::optional<std::span<const ProviderInfo>> providers`
  - `std::optional<std::span<const InstrumentationInfo>> instrumentation`
  - `std::optional<std::span<const PermissionInfo>> permissions`
  - `std::optional<std::span<const std::string_view>> requested_permissions`
  - `std::optional<std::span<const RequestedPermissionFlag>> requested_permissions_flags`
  - `std::optional<std::span<const Attribution>> attributions`
  - `std::optional<std::span<const Signature>> signatures` (deprecated)
  - `std::optional<std::reference_wrapper<const SigningInfo>> signing_info`
  - `std::optional<std::span<const ConfigurationInfo>> config_preferences`
  - `std::optional<std::span<const FeatureInfo>> req_features`
  - `std::optional<std::span<const FeatureGroupInfo>> feature_groups`
  - `InstallLocation install_location = InstallLocation::INTERNAL_ONLY`
  - `bool is_stub`
  - `bool core_app`
  - `bool required_for_all_users`
  - `std::optional<std::string_view> restricted_account_type`
  - `std::optional<std::string_view> required_account_type`
  - `std::optional<std::string_view> overlay_target`
  - `std::optional<std::string_view> target_overlayable_name`
  - `std::optional<std::string_view> overlay_category`
  - `int32_t overlay_priority`
  - `bool overlay_is_static`
  - `int32_t compile_sdk_version`
  - `std::optional<std::string_view> compile_sdk_version_codename`
  - `bool is_apex`
  - `bool is_active_apex`
- [X] T048 [US1] Declare private fields `archive_time_millis_` (int64_t) and `apex_package_name_` (std::optional<std::string>) in `core/cpp/include/android/content/pm/package_info.h`
- [X] T049 [US1] Declare static constants in `core/cpp/include/android/content/pm/package_info.h`:
  - `static constexpr RequestedPermissionFlag REQUESTED_PERMISSION_REQUIRED`
  - `static constexpr RequestedPermissionFlag REQUESTED_PERMISSION_GRANTED`
  - `static constexpr RequestedPermissionFlag REQUESTED_PERMISSION_NEVER_FOR_LOCATION`
  - `static constexpr RequestedPermissionFlag REQUESTED_PERMISSION_IMPLICIT`
  - `static constexpr InstallLocation INSTALL_LOCATION_UNSPECIFIED`
  - `static constexpr InstallLocation INSTALL_LOCATION_AUTO`
  - `static constexpr InstallLocation INSTALL_LOCATION_INTERNAL_ONLY`
  - `static constexpr InstallLocation INSTALL_LOCATION_PREFER_EXTERNAL`
- [X] T050 [US1] Declare all methods in `core/cpp/include/android/content/pm/package_info.h`:
  - `PackageInfo() = default`
  - `int64_t long_version_code() const`
  - `void set_long_version_code(int64_t)`
  - `static int64_t compose_long_version_code(int32_t, int32_t)`
  - `bool is_overlay_package() const`
  - `bool is_static_overlay_package() const`
  - `int64_t archive_time_millis() const`
  - `void set_archive_time_millis(int64_t)`
  - `std::optional<std::string_view> apex_package_name() const`
  - `void set_apex_package_name(std::string_view)`
  - `std::string to_string() const`
  - `int describe_contents() const`
  - `void write_to_parcel(void& parcel, int32_t) const`
  - `explicit PackageInfo(void& parcel)`
- [X] T051 [US1] Implement `long_version_code()` in `core/cpp/src/android/content/pm/package_info.cpp` — combines `version_code_major << 32 | version_code`
- [X] T052 [US1] Implement `set_long_version_code()` in `core/cpp/src/android/content/pm/package_info.cpp` — splits into `version_code_major` (upper 32) and `version_code` (lower 32)
- [X] T053 [US1] Implement `compose_long_version_code()` static method in `core/cpp/src/android/content/pm/package_info.cpp` — identical logic to Java
- [X] T054 [US1] Implement `is_overlay_package()` in `core/cpp/src/android/content/pm/package_info.cpp` — checks overlay-related fields
- [X] T055 [US1] Implement `is_static_overlay_package()` in `core/cpp/src/android/content/pm/package_info.cpp` — checks overlay_is_static field
- [X] T056 [US1] Implement `archive_time_millis()` getter and `set_archive_time_millis()` setter in `core/cpp/src/android/content/pm/package_info.cpp`
- [X] T057 [US1] Implement `apex_package_name()` getter and `set_apex_package_name()` setter in `core/cpp/src/android/content/pm/package_info.cpp`
- [X] T058 [US1] Implement `to_string()` in `core/cpp/src/android/content/pm/package_info.cpp` — produces human-readable output of all fields
- [X] T059 [US1] Implement `describe_contents()` in `core/cpp/src/android/content/pm/package_info.cpp` — returns 0
- [X] T060 [US1] Implement `write_to_parcel()` in `core/cpp/src/android/content/pm/package_info.cpp` — serializes fields in Java field order per contract
- [X] T061 [US1] Implement `PackageInfo(void& parcel)` constructor in `core/cpp/src/android/content/pm/package_info.cpp` — deserializes fields in Java field order per contract
- [X] T062 [US1] Add `// @Deprecated` comments to `version_code` and `signatures` fields in `package_info.h`
- [X] T063 [US1] Add `// @hide` comments to all `@hide`-annotated fields in `package_info.h`

**Checkpoint**: User Story 1 is fully functional — `PackageInfo` can be instantiated, populated, and serialized/deserialized

---

## Phase N: Polish & Cross-Cutting Concerns

**Purpose**: Improvements that affect multiple user stories

- [ ] T064 [P] Verify `package_info.h` compiles with `-Wall -Werror -Wextra` on clang 18+
- [ ] T065 [P] Verify CMake custom command for `package_info_generator` builds and runs successfully
- [ ] T066 [P] Run `ctest -R PackageInfoTests` (or equivalent) and confirm all tests pass
- [ ] T067 [P] Validate `quickstart.md` instructions work end-to-end (generate headers, run tests)
- [ ] T068 [P] Verify all public methods in `package_info.h` have Doxygen-style `/// @brief` documentation
- [ ] T069 [P] Confirm `PackageInfo` struct has zero heap allocation and zero virtual dispatch (zero-cost abstraction)
- [ ] T070 [P] Run `ctest` on the full `framework_tests` executable to confirm no regressions in existing tests
- [ ] T071 [P] Verify CMake dependency tracking — modifying a `package-info.java` file triggers header regeneration

---

## Dependencies & Execution Order

### Phase Dependencies

- **Setup (Phase 1)**: No dependencies — can start immediately
- **Foundational (Phase 2)**: Depends on Setup completion — BLOCKS all user story work
- **User Story 1 (Phase 3)**: Depends on Foundational phase completion
- **Polish (Final Phase)**: Depends on User Story 1 being complete

### User Story Dependencies

- **User Story 1 (P1)**: Can start after Foundational (Phase 2) — No dependencies on other stories

### Within Each User Story

- Tests MUST be written and FAIL before implementation (Constitution Principle III)
- Header declaration before implementation
- Core implementation before integration
- Story complete before moving to next phase

### Parallel Opportunities

- All Setup tasks (T001–T005) can run in parallel (different files)
- All Foundational tasks (T006–T013) can run in parallel (different files, no cross-dependencies)
- All test tasks for User Story 1 (T014–T043) can run in parallel (different test functions, same file but no inter-test dependencies)
- All implementation tasks for User Story 1 (T044–T063) can run in parallel (header types first, then methods in separate functions)
- All Polish tasks (T064–T071) can run in parallel (different verification concerns)

---

## Parallel Example: User Story 1

```bash
# Launch all test tasks in parallel:
Task: "Test: PackageInfo default construction" (T014)
Task: "Test: package_name field" (T015)
Task: "Test: version_name nullable" (T016)
Task: "Test: long_version_code()" (T022)
Task: "Test: set_long_version_code()" (T023)
...

# Launch all implementation tasks in parallel:
Task: "Write header guard and includes" (T044)
Task: "Implement enum classes" (T045)
Task: "Declare PackageInfo class with all 42 fields" (T047)
Task: "Implement long_version_code()" (T051)
Task: "Implement set_long_version_code()" (T052)
Task: "Implement compose_long_version_code()" (T053)
...
```

---

## Implementation Strategy

### MVP First (User Story 1 Only)

1. Complete Phase 1: Setup
2. Complete Phase 2: Foundational (CRITICAL — blocks all stories)
3. Complete Phase 3: User Story 1
4. **STOP and VALIDATE**: Test User Story 1 independently
5. Deploy/demo if ready

### Incremental Delivery

1. Complete Setup + Foundational → Foundation ready
2. Add User Story 1 → Test independently → Deploy/Demo (MVP!)
3. Polish → Verify no regressions

### Parallel Team Strategy

With multiple developers:

1. Team completes Setup + Foundational together
2. Once Foundational is done:
   - Developer A: Write all tests (T014–T043)
   - Developer B: Write header declaration (T044–T050)
   - Developer C: Implement methods (T051–T063)
3. All integrate and verify together

---

## Notes

- [P] tasks = different files, no dependencies
- [Story] label maps task to specific user story for traceability
- Each user story should be independently completable and testable
- Verify tests fail before implementing (Constitution Principle III)
- Commit after each task or logical group
- Stop at any checkpoint to validate story independently
- Avoid: vague tasks, same file conflicts, cross-story dependencies that break independence
