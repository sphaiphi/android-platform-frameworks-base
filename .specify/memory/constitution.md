<!--
  Sync Impact Report
  ==================
  Version change: 0.0.0 (template) -> 1.0.0
  Modified principles: N/A (first generation)
  Added sections: Core Principles (I-V), Dependency Management, Code Quality,
    AI Agent Guidance, Governance
  Removed sections: None
  Templates requiring updates:
    - .specify/templates/plan-template.md: "Constitution Check" gate is generic - OK
    - .specify/templates/spec-template.md: No constitution references - OK
    - .specify/templates/tasks-template.md: No constitution references - OK
    - .specify/templates/checklist-template.md: No constitution references - OK
  Deferred TODOs: None
-->

# Android Framework Core Constitution

## Core Principles

### I. Safety-First Design

All code MUST adhere to the five safety dimensions: Type, Bounds, Lifetime, Initialization, and Error Handling. These dimensions are non-negotiable and take precedence over performance or convenience.

**Why:** The Android framework is foundational system software. A single safety violation can cascade into system-wide instability or security vulnerabilities. Safety must be engineered in, not tested in.

**How to apply:** Every component MUST be verified against all five safety dimensions before being considered complete. Use `std::span` for bounds safety, smart pointers for lifetime safety, `enum class` for type safety, and `std::expected` for error safety. No pointer arithmetic. No manual `new`/`delete`.

### II. Zero-Cost Abstractions

Every abstraction MUST have zero runtime overhead compared to its hand-written C equivalent. If an abstraction adds measurable overhead, it MUST be justified or replaced with a more efficient alternative.

**Why:** The framework targets NDK developers who require performance parity with C for system-level components. Abstractions that hide cost defeat the purpose of a native framework.

**How to apply:** Prefer static polymorphism (templates, concepts) over virtual functions. Use inline-friendly patterns. Profile abstractions before merging. If a design choice cannot be proven zero-cost, default to the simpler, lower-level alternative.

### III. Test-Driven Development (NON-NEGOTIABLE)

Tests MUST be written and confirmed failing before implementation begins (Red phase). Implementation proceeds only until tests pass (Green phase). Refactoring occurs only while tests remain passing.

**Why:** TDD ensures that requirements are precisely specified before code is written, preventing over-engineering and guaranteeing that implementation matches intent.

**How to apply:** Follow the Red-Green-Refactor cycle strictly. Target >80% code coverage for all modules. Use GoogleTest/GoogleMock for unit tests and Android CTS for compliance validation. Every module MUST have corresponding tests covering both success and failure cases.

### IV. Plan as Source of Truth

All work MUST be tracked in `conductor/tracks/` plan files. The plan MUST be updated before work begins (`[ ]` -> `[~]`) and after completion (`[~]` -> `[x]` with commit SHA). No work exists outside the plan.

**Why:** Centralized task tracking ensures traceability, prevents orphaned work, and enables phase-level verification and checkpointing.

**How to apply:** Update plan.md before starting any task. Attach task summaries as git notes to commits. Record commit SHAs in plan updates. Phase completion requires checkpoint commits with verification reports.

### V. Tech Stack Deliberation

Changes to the technology stack MUST be documented in `conductor/tech-stack.md` BEFORE implementation. Deviations require stopping implementation, updating the tech stack doc with a dated note explaining the change, then resuming.

**Why:** The tech stack is a deliberate architectural decision. Undocumented changes erode consistency, introduce incompatible patterns, and make code review impossible.

**How to apply:** Before adopting any new library, language feature, or build tool, check `conductor/tech-stack.md`. If it does not cover your choice, document it there first with a date and rationale.

## Dependency Management

**Approved Technology Stack:**

| Category | Technology | Standard/Version | Reference |
|---|---|---|---|
| Language | C++ | C++23 | [cppreference C++23](https://cppreference.com/w/cpp/23.html) |
| Safety Standards | C++ Core Guidelines | Current | Safety-First Idioms (Type, Bounds, Lifetime, Init, Error) |
| Build System (On-Device) | ndk-build | NDK r29 | [NDK Reference](https://developer.android.com/ndk/reference) |
| Build System (Host/Tests) | CMake | Latest | CMakeLists.txt |
| IPC | AIDL | Stable AIDL APIs | [AIDL Language](https://source.android.com/docs/core/architecture/aidl/aidl-language) |
| Testing | GoogleTest/GoogleMock | Latest | ctest / GoogleTest docs |
| Validation | Android CTS | Platform-matched | CTS framework tests |
| Async | C++23 Coroutines | C++23 | For non-blocking operations |
| Error Handling | std::expected | C++23 | For recoverable errors |
| Reference | Java Sources | AOSP matching branch | Functional baseline only |

**Rules:**
- All dependencies MUST be documented in `conductor/tech-stack.md` before use.
- Java sources in `core/java/` serve as the functional reference baseline for C++ reimplementation; they are NOT built or executed.
- libbinder_ndk headers: platform developers use headers from both NDK-shipped (`include_ndk`) and SDK-shipped (`include_cpp`) paths. Application developers only receive NDK-shipped headers.
- Branch alignment: `lineageos-23.0` for track work, `main` for PRs.

## Code Quality

**C++23 Strictness:**
- Adhere strictly to C++23 standards. Utilize modern features (`std::expected`, concepts, ranges) to express intent and ensure safety.
- No C++17 or earlier features unless justified by NDK r29 compatibility constraints.

**Safety Idioms (MUST for all code):**
- **Type Safety:** Use strong types and `enum class`. Avoid primitive obsession.
- **Bounds Safety:** Prefer `std::span` and standard containers. No pointer arithmetic.
- **Lifetime Safety:** Strict RAII for all resources. Smart pointers only; no manual `new`/`delete`.
- **Initialization Safety:** All objects MUST be fully initialized before use. Uninitialized reads are prohibited.
- **Error Safety:** Use `std::expected<T, E>` for recoverable errors. `std::optional` denotes absence of a value, NOT an error state. Exceptions are reserved for truly exceptional, unrecoverable circumstances (e.g., OOM).

**Architectural Guidelines:**
- **Static Polymorphism First:** Prioritize templates and concepts over virtual functions to minimize runtime overhead.
- **Asynchronous Patterns:** Use coroutines and modern async primitives instead of callback patterns.
- **Resource Management:** Every resource (memory, file descriptors, synchronization primitives) MUST be managed by an RAII-compliant object.
- **Namespace Structure:** Organize code within `android::*` namespaces (e.g., `android::view`, `android::os`) to reflect the framework's layered architecture.

**Performance Requirements:**
- Zero-cost abstractions: design for performance parity with C.
- Target >80% code coverage for all modules.
- No performance regressions validated against CTS benchmarks.

**Documentation Requirements:**
- All public functions and methods MUST be documented.
- Implementation MUST follow spec documentation in `core/cpp/specs/` when available.

## AI Agent Guidance

**Workflow Discipline:**
1. Select the next available task from the plan in sequential order.
2. Mark task in progress (`[ ]` -> `[~]`) before beginning work.
3. Write failing tests first (Red phase) - run and confirm failure.
4. Implement minimum code to pass tests (Green phase).
5. Refactor while tests pass (optional but recommended).
6. Verify coverage (>80%).
7. Attach task summary as git note to the commit.
8. Mark task complete (`[x]`) with 7-character commit SHA.
9. Commit plan update.

**Spec-Driven Development:**
When a spec exists in `core/cpp/specs/`:
1. Read and resolve all "Open Questions" or "TBD" sections in the spec.
2. Write failing unit tests based strictly on the updated specification.
3. Implement C++ code to satisfy the spec and pass tests.
4. Validate against Android CTS for platform compliance.
5. Follow standard completion workflow (steps 1-9 above).

**Phase Completion Protocol:**
After completing a task that concludes a phase:
1. Determine phase scope via git diff from previous checkpoint SHA.
2. Verify test coverage for all changed code files; create missing tests.
3. Execute automated tests with announced command.
4. Propose detailed manual verification plan for user review.
5. Await explicit user confirmation before proceeding.
6. Create checkpoint commit with verification report as git note.
7. Record checkpoint SHA in plan.

**Quality Gates (all MUST pass before marking task complete):**
- [ ] All tests pass
- [ ] Code coverage >80%
- [ ] Code follows project coding standards
- [ ] All public functions/methods are documented
- [ ] Type safety enforced
- [ ] No linting or static analysis errors
- [ ] No security vulnerabilities introduced

**Commit Message Format:**
```
<type>(<scope>): <description>

Types: feat, fix, docs, style, refactor, test, chore
```

## Governance

**Authority:** This constitution supersedes all other development practices, patterns, and conventions within this project. All PRs, reviews, and implementations MUST verify compliance.

**Amendment Procedure:**
1. Propose changes to `conductor/` documentation files first (product.md, tech-stack.md, workflow.md, patterns.md).
2. Update this constitution to reflect the documented changes.
3. Increment version per semantic versioning:
   - MAJOR: Backward incompatible governance or principle removals/redefinitions.
   - MINOR: New principle or section added, or materially expanded guidance.
   - PATCH: Clarifications, wording fixes, typo corrections, non-semantic refinements.
4. Propagate changes to dependent templates (plan-template.md, spec-template.md, tasks-template.md, checklist-template.md).
5. Commit with message: `docs: amend constitution to vX.Y.Z (<summary>)`.

**Compliance Review:**
- All AI agent sessions MUST check constitution compliance before implementation.
- The `conductor/workflow.md` Quality Gates checklist is mandatory for task completion.
- Deviations from the tech stack MUST follow the stop-document-resume protocol (see Principle V).

**Non-Negotiables:**
- TDD is mandatory (Principle III).
- Safety dimensions are non-negotiable (Principle I).
- Plan tracking is mandatory (Principle IV).

**Version**: 1.0.0 | **Ratified**: 2026-05-10 | **Last Amended**: 2026-05-10
