# Android Framework Core Constitution
**Version:** 1.0.0 | **Ratified:** 2026-05-10

---

## Principles

### I — Safety-First (non-negotiable)
Every component MUST satisfy all five dimensions before marking complete:

| Dimension | Rule |
|---|---|
| Type | `enum class` and strong types only. No primitive obsession. |
| Bounds | `std::span` and standard containers only. No pointer arithmetic. |
| Lifetime | RAII throughout. Smart pointers only. No `new`/`delete`. |
| Initialization | All objects fully initialized before use. No uninitialized reads. |
| Error | `std::expected<T,E>` for recoverable errors. `std::optional` = absence, not error. Exceptions = unrecoverable only (e.g. OOM). |

### II — Zero-Cost Abstractions
- Static polymorphism (templates, concepts) over virtual functions.
- Every abstraction MUST have zero measurable overhead vs. C equivalent.
- If overhead exists: justify or replace. When uncertain, use the lower-level alternative.

### III — TDD (non-negotiable)
Red → Green → Refactor. Strictly in that order.
- Write failing test → confirm failure → implement minimum code → confirm pass → refactor.
- Coverage target: >80% per module.
- Test frameworks: GoogleTest/GoogleMock (unit), Android CTS (compliance).

### IV — Spec as Source of Truth
- All work tracked in `.specify/specs/<feature-id>/tasks.md`.
- Before starting: `[ ]` → `[~]`. After completion: `[~]` → `[x] <7-char-sha>`.
- Log to `tasks.md.progress` after each task.
- No work exists outside the spec pipeline.

### V — Tech Stack Deliberation
- Any new library, language feature, or build tool MUST be documented in **Dependency Management** below and in the feature's `plan.md` before use.
- If undocumented: stop → update constitution + `plan.md` with date and rationale → resume.

---

## Dependency Management

| Category | Technology | Version |
|---|---|---|
| Language | C++ | C++23 |
| Safety | C++ Core Guidelines | Current |
| Build (on-device) | ndk-build | NDK r29 |
| Build (host/tests) | CMake | Latest |
| IPC | AIDL | Stable APIs |
| Testing | GoogleTest/GoogleMock | Latest |
| Validation | Android CTS | Platform-matched |
| Async | C++23 Coroutines | C++23 |
| Error handling | `std::expected` | C++23 |
| Reference baseline | Java sources (AOSP) | Matching branch — read only, not built |

**Rules:**
- No C++17 or earlier unless justified by NDK r29 compatibility.
- Java sources in `core/java/` = functional reference only. Not built or executed.
- libbinder_ndk: platform devs use `include_ndk` + `include_cpp`; app devs use `include_ndk` only.
- Branch: `lineageos-23.0` for feature work, `main` for PRs.
- New dependencies: document here first, then use.

---

## Code Quality

- Namespaces: `android::*` (e.g. `android::view`, `android::os`).
- Async: coroutines and modern primitives. No callbacks.
- All public functions/methods MUST be documented.
- Follow spec in `core/cpp/specs/` when present.
- No performance regressions vs. CTS benchmarks.

---

## AI Agent Workflow

### Per-Task Sequence
1. Read `.specify/memory/constitution.md` (this file).
2. Read `.specify/specs/<feature-id>/thinking.md` → implementation design blueprint.
3. Read `.specify/specs/<feature-id>/tasks.md` → pick next `[ ]` task in order.
4. Mark `[~]` before starting.
5. **Red:** write failing tests → run → confirm failure.
6. **Green:** implement minimum code → run → confirm pass.
7. **Refactor** while tests remain passing.
8. Verify coverage >80%.
9. `git notes append -m "<task summary>"` on commit.
10. Mark `[x] <sha>` in `tasks.md`. Log to `tasks.md.progress`.

### Spec-Driven Steps (when `core/cpp/specs/` or `spec.md` exists)
1. Resolve all "Open Questions" / "TBD" in spec before writing any code.
2. Write failing tests from spec.
3. Implement to pass.
4. Validate against Android CTS.
5. Continue per-task sequence (steps 8–10).

### Artifact Reading Order
```
constitution.md          ← constraints (this file)
thinking.md              ← implementation design
tasks.md                 ← what to build, acceptance criteria
plan.md                  ← architecture reference for ambiguities
data-model.md            ← schema
contracts/               ← API shapes
```

### Phase Completion
After the final task in a phase:
1. `git diff <prev-checkpoint-sha>` → determine phase scope.
2. Verify >80% coverage for all changed files; add missing tests.
3. Run tests → announce command and output.
4. Propose manual verification plan → await explicit user confirmation.
5. Checkpoint commit with verification report as git note.
6. Record checkpoint SHA in `tasks.md.progress`.

### Quality Gates (all MUST pass before `[x]`)
- [ ] All tests pass
- [ ] Coverage >80%
- [ ] Coding standards met
- [ ] All public APIs documented
- [ ] Type safety enforced (Principle I)
- [ ] No linting / static analysis errors
- [ ] No security vulnerabilities
- [ ] Principles I–V verified

### Commit Format
```
<type>(<scope>): <description>
```
Types: `feat` `fix` `docs` `style` `refactor` `test` `chore`

---

## Governance

**Authority:** This constitution supersedes all other conventions. All PRs and implementations MUST verify compliance.

**Amendment:**
1. Propose on a dedicated branch.
2. Update this constitution + affected feature `plan.md`.
3. Version bump:
   - MAJOR — principle removal or redefinition
   - MINOR — new principle or section
   - PATCH — clarification or wording fix
4. Commit: `docs: amend constitution to vX.Y.Z (<summary>)`

**Non-negotiables:** Principles I (Safety), III (TDD), IV (Spec tracking).