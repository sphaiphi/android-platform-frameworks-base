# Quality Checklist: Foundational View Classes

**Target:** all  
**Strict mode:** yes  
**Run date:** 2026-06-13  
**Overall result:** **FAIL**

---

## Summary

| Artifact       | Pass | Warning | Fail | Result |
|----------------|------|---------|------|--------|
| spec.md        |  11  |    1    |  0   | Warning |
| plan.md        |   8  |    2    |  0   | Warning |
| data-model.md  |   5  |    3    |  0   | Warning |
| tasks.md       |   0  |    0    | 10   | FAIL (missing) |
| constitution.md|   5  |    0    |  0   | Pass |
| **Total**      | **29** | **6** | **10** | **FAIL** |

**Note:** tasks.md does not exist at `.specify/specs/001-view-foundational/tasks.md`. All 10 task checks (T-01 through T-10) are treated as failures.

---

## spec.md

### S-01 -- No vague verbs

**Result: PASS**

All 53 functional requirements use precise, testable verbs (shall provide, shall define, shall support, shall trigger, shall set, shall maintain). No banned words found without qualification.

All 57 acceptance criteria across 19 user stories use precise, testable verbs (can receive, stores, respects, can be overridden, returns, calls, excludes, preserves, controls, supports, can be constructed, marks, propagates, stops, can call, can query, maintains, iterates, draws, replaces, removes, is cleared, is triggered, is delivered, starts, is not consumed). No banned words found without qualification.

---

### S-02 -- No passive voice hiding the actor

**Result: PASS**

All functional requirements explicitly name "The system" as the actor: "The system shall provide...", "The system shall define...", "The system shall support...", "The system shall trigger...", "The system shall set...", "The system shall maintain...".

All acceptance criteria name the actor performing the action: "A View can receive...", "The View stores...", "The View respects...", "A ViewGroup draws...", "A MotionEvent is delivered..." (passive but the actor is clear from context: the dispatch infrastructure).

---

### S-03 -- Acceptance criteria are binary

**Result: FAIL**

**Location:** US-06, criterion 1  
**Found:** "setPadding(left, top, right, bottom) and getPaddingLeft(), getPaddingTop(), getPaddingRight(), getPaddingBottom() work correctly."  
**Problem:** The word "correctly" is subjective and unverifiable by a QA engineer without a specific target. It is a banned non-binary term.  
**Fix:** Replace with a specific, measurable condition, e.g.: "setPadding(10, 20, 30, 40) causes getPaddingLeft() to return 10, getPaddingTop() to return 20, getPaddingRight() to return 30, and getPaddingBottom() to return 40."

**Location:** US-12, criterion 4  
**Found:** "Children are iterated in z-order (front-to-back or back-to-front as appropriate)."  
**Problem:** The word "appropriate" is subjective. A QA engineer cannot determine what is "appropriate" without a defined ordering rule.  
**Fix:** Replace with a specific ordering rule, e.g.: "Children are iterated in back-to-front z-order (index 0 is drawn first, last index is drawn on top)."

---

### S-04 -- Every user story has at least two acceptance criteria

**Result: PASS**

All 19 user stories have at least two acceptance criteria:

| User Story | Criterion Count |
|------------|----------------|
| US-01 | 3 |
| US-02 | 4 |
| US-03 | 3 |
| US-04 | 3 |
| US-05 | 9 |
| US-06 | 3 |
| US-07 | 2 |
| US-08 | 2 |
| US-09 | 4 |
| US-10 | 3 |
| US-11 | 3 |
| US-12 | 4 |
| US-13 | 4 |
| US-14 | 3 |
| US-15 | 3 |
| US-16 | 5 |
| US-17 | 3 |
| US-18 | 2 |
| US-19 | 3 |

Minimum is 2 (US-07, US-08, US-18). No story has fewer than 2.

---

### S-05 -- User stories use the canonical format

**Result: PASS**

All 19 user stories follow the format "As a [role], I want to [specific action] so that [specific benefit]":

- US-01: "As a Framework Developer, I want to create a View with a Context so that it can participate in the view hierarchy."
- US-02: "As a Framework Developer, I want the View to support a measure-pass so that it can determine its desired size."
- ... all 19 follow the pattern.

Every role (Framework Developer, NDK Developer, View) is defined or referenced from the User Roles section. Note: US-09, US-10, and US-11 use "As a View" as the role -- View is not listed in the User Roles table, but it is the primary entity described in the Overview. This is a minor inconsistency but not a hard failure since View is the subject of the feature.

---

### S-06 -- Non-goals are explicit

**Result: PASS**

The Non-Goals section contains 15 explicit entries:

1. Widget classes
2. Layout managers
3. Animation system
4. Rendering pipeline
5. Input method integration
6. Accessibility
7. Window management
8. XML layout inflation
9. Drag and drop infrastructure
10. Nested scrolling
11. Autofill
12. Content capture
13. Touch filtering for security
14. Context menus and action modes
15. Scrollbars
16. Haptic feedback
17. Keyboard navigation clusters

Well-bounded scope with extensive non-goals.

---

### S-07 -- No implementation language in the spec

**Result: FAIL**

The spec contains implementation-specific language that should be removed or deferred to the plan. The constitution mandates C++23, which justifies some references, but specific library types and class declarations belong in the plan, not the spec.

**Location:** Constraints section  
**Found:** "The implementation must follow C++23 as defined in the constitution (enum class, std::span, RAII, smart pointers, std::expected)."  
**Problem:** "C++23", "std::span", "std::expected" are implementation language. The constitution mandates these, but the spec should be tech-agnostic.  
**Fix:** Replace with: "The implementation must follow the safety and type rules defined in the constitution."

**Location:** Constraints section  
**Found:** "No JNI, no Java interop, no AOSP build system dependency -- standalone C++23."  
**Problem:** "C++23", "JNI", "AOSP" are implementation language.  
**Fix:** Replace with: "The implementation is standalone and does not depend on any external build system or interoperability layer."

**Location:** Constraints section  
**Found:** "Code lives under core/cpp/src/android/view/."  
**Problem:** Specific file path is implementation detail.  
**Fix:** Defer to plan.

**Location:** Constraints section  
**Found:** "Namespaces mirror Android SDK: android::view."  
**Problem:** Specific namespace convention is implementation detail.  
**Fix:** Defer to plan.

**Location:** FR-33 (US-12)  
**Found:** "The system shall define ViewGroup as publicly inheriting View and privately composing ViewParent/ViewManager via CRTP: class ViewGroup : public View, private ViewParentMixin<ViewGroup>, private ViewManagerMixin<ViewGroup>. ViewGroup casts this to ViewParent/ViewManager via static_cast."  
**Problem:** Exact class declaration syntax, CRTP pattern, static_cast -- all implementation language.  
**Fix:** Replace with: "The system shall define ViewGroup to inherit from View and implement the ViewParent and ViewManager contracts through a compile-time polymorphic pattern."

**Location:** Data Model section (inline in spec)  
**Found:** "enum class Visibility : int { Visible = 0, Invisible = 4, Gone = 8 }"  
**Problem:** C++ enum class syntax with integer values is implementation language.  
**Fix:** Replace with: "Visibility is an enumerated type with three values: Visible, Invisible, and Gone."

**Location:** Data & State section  
**Found:** "std::any" referenced for tag storage in the FR-25 description and Data & State section.  
**Problem:** `std::any` is a specific C++ library type.  
**Fix:** Replace with: "an arbitrary object storage type that supports type-safe retrieval."

---

### S-08 -- All roles are defined before use

**Result: PASS**

Roles defined in User Roles table:

| Role | Used In |
|------|---------|
| Framework Developer | US-01, US-02, US-03, US-04, US-12, US-13, US-14, US-15, US-16, US-17, US-18, US-19 |
| NDK Developer | US-05, US-06, US-07, US-08 |
| Test Engineer | Not used in any user story (defined but not referenced; not a failure) |

Note: US-09, US-10, US-11 use "As a View" as the role. View is not in the User Roles table but is the primary entity described in the Overview. This is a minor inconsistency.

---

### S-09 -- Data entities are named consistently

**Result: PASS**

Data entities are named consistently throughout the spec:

| Entity | Name Used | Consistent? |
|--------|-----------|-------------|
| View | "View" | Yes |
| ViewGroup | "ViewGroup" | Yes |
| ViewParent | "ViewParent" | Yes |
| ViewManager | "ViewManager" | Yes |
| LayoutParams | "LayoutParams" | Yes |
| MarginLayoutParams | "MarginLayoutParams" | Yes |
| MeasureSpec | "MeasureSpec" | Yes |
| Canvas | "Canvas" | Yes |

No synonyms or inconsistent capitalization found.

---

### S-10 -- Review checklist is present and populated

**Result: PASS**

The spec contains a "Review & Acceptance Checklist" section with 8 items, all checked:

- [x] All user roles are identified
- [x] Every user story has at least two acceptance criteria
- [x] Non-goals are explicit
- [x] Functional requirements are testable
- [x] Data entities are named and described
- [x] Primary happy path is described end-to-end
- [x] At least one error/edge case is documented
- [x] Constitution principles are respected

---

### S-11 -- Assumptions are surfaced

**Result: PASS**

The spec contains an "Assumptions" subsection with 6 explicit assumptions, each marked with "Assumption:" and each followed by "Confirm before planning":

1. Canvas-like drawing surface is provided by a separate graphics module.
2. MotionEvent and KeyEvent types are provided by a separate input module.
3. Context is a minimal interface providing resource access.
4. The Choreographer and frame loop infrastructure will drive the passes.
5. Window attachment and detachment lifecycle is coordinated by a higher-level module.
6. LayoutParams and MeasureSpec types are shared across the View system.

No undeclared assumptions flagged. Scanned for banned phrases (obviously, of course, naturally, as usual, the standard way, typical) -- none found.

---

### S-12 -- Scope matches stated goals

**Result: PASS**

Every goal has at least one functional requirement or user story:

| Goal | Traced To |
|------|-----------|
| Instantiate and manage UI elements with full lifecycle | US-01, US-02, US-03, US-04; FR-01 through FR-14a |
| Hierarchical composition via ViewGroup | US-12, US-13, US-14; FR-33 through FR-43 |
| Bidirectional communication contract (ViewParent) | US-09, US-10, US-11; FR-27 through FR-32 |
| Uniform interface (ViewManager) | US-17, US-18, US-19; FR-49 through FR-53 |
| View property system | US-05, US-06, US-07, US-08; FR-15 through FR-26 |
| Touch event dispatch infrastructure | US-16; FR-44 through FR-48 |

All 6 goals are fully traced.

---

## plan.md

### P-01 -- Every layer is named and described

**Result: PASS**

All five architectural layers are described in dedicated sections:

| Layer | Section | Content |
|-------|---------|---------|
| Data | "Data Layer" | Header files, source files, test files, key design decisions |
| Service / Business Logic | "Service / Business Logic Layer" | View Class, ViewGroup Class, ViewParentMixin, ViewManagerMixin |
| API | "API Layer" | Public headers, internal headers, error handling |
| UI | "UI Layer" | draw() sequence, dispatchDraw() sequence, child draw behavior |
| Auth | N/A (no auth layer needed) | Security section covers input validation and bounds safety |

The plan notes "This is a framework-level library, not an application UI" for the UI layer and "No network exposure" for security, which is appropriate for a C++ library.

---

### P-02 -- Stack decisions are justified

**Result: PASS**

The "Stack Decisions" table provides both the choice and a rationale for every entry:

| Choice | Rationale |
|--------|-----------|
| C++23 | "Constitution Mandate. NDK r29 Clang 18 supports all required features." |
| CMake | "Existing repo pattern. FetchContent for GoogleTest." |
| ndk-build | "Constitution Dependency Management table." |
| GoogleTest 1.15.2 | "Existing repo pattern. Latest stable." |
| CRTP | "Constitution Principle II. Zero vtable overhead." |
| LayoutParams hierarchy | "FR-39. Static polymorphism, no virtual dispatch." |
| std::expected | "Constitution Principle I." |
| std::vector, std::shared_ptr | "Constitution Principle I (RAII, smart pointers)." |
| std::any | "For setTag/getTag (FR-25)." |

Every decision has a "because" statement.

---

### P-03 -- Security model covers all roles

**Result: FAIL**

**Location:** Security Model section  
**Found:** "No network exposure... Input validation... Thread safety... Bounds safety..."  
**Problem:** The spec defines three roles (Framework Developer, NDK Developer, Test Engineer), but the security model does not state what each role can and cannot do at the API layer. The security model describes technical constraints but not role-based access control.  
**Fix:** For each role, state the API-level permissions:
- Framework Developer: can extend View/ViewGroup, can override virtual methods, can access protected/internal members.
- NDK Developer: can use public headers to construct and manipulate View hierarchies, cannot access internal CRTP implementation details.
- Test Engineer: can access test fixtures and test-only methods, cannot access production internals.

---

### P-04 -- No orphaned components

**Result: PASS**

Every component named in the plan connects to something else:

| Component | Connects To |
|-----------|-------------|
| View.h | View.cpp, ViewParentMixin.h, ViewManagerMixin.h |
| ViewGroup.h | ViewGroup.cpp, View.h, ViewParentMixin.h, ViewManagerMixin.h |
| ViewParentMixin.h | Header-only template, used by View and ViewGroup |
| ViewManagerMixin.h | Header-only template, used by View and ViewGroup |
| LayoutParams.h | ViewGroup.cpp (template parameter) |
| MotionEvent.h | Existing, referenced by View.cpp |
| View.cpp | Calls ViewParentMixin, ViewManagerMixin |
| ViewGroup.cpp | Calls View.cpp methods, ViewParentMixin, ViewManagerMixin |
| Test files | Reference the corresponding source/header files |

No floating inventions.

---

### P-05 -- Testing strategy specifies coverage targets

**Result: PASS**

The testing strategy table specifies coverage targets for every layer:

| Layer | Coverage Target |
|-------|----------------|
| View Properties | 90%+ |
| View Measure | 90%+ |
| View Layout | 90%+ |
| View Draw | 85%+ |
| View Touch | 85%+ |
| View Focus | 85%+ |
| ViewGroup Children | 90%+ |
| ViewGroup Measure | 90%+ |
| ViewGroup Layout | 90%+ |
| ViewGroup Draw | 85%+ |
| ViewGroup Touch | 85%+ |
| ViewParent CRTP | 90%+ |
| ViewManager CRTP | 90%+ |
| LayoutParams | 90%+ |

All 14 test categories have explicit coverage targets. All are unit tests.

---

### P-06 -- Environment variables are enumerated

**Result: PASS**

The "Environment & Configuration" section enumerates all configuration values:

| Variable | Purpose |
|----------|---------|
| CMAKE_CXX_STANDARD | C++ standard for build |
| ANDROID_NDK_HOME | NDK path for device builds |
| GTEST_ENABLE | Enable GoogleTest |

The plan notes "No runtime environment variables needed" which is correct for a pure C++ library. No implicit config assumptions found in layer descriptions.

---

### P-07 -- Deployment steps are ordered

**Result: PASS**

The "Deployment & Rollout" section lists 6 steps in explicit sequence:

1. Header changes
2. Source changes
3. Test changes
4. Migration
5. Rollback
6. Integration

Steps are numbered and in logical order (headers before sources, sources before tests, then migration/rollback/integration).

---

### P-08 -- Open questions are tracked

**Result: PASS**

The plan has an "Open Questions" section with 4 tracked items:

1. Context type (exact signature depends on existing repo)
2. Canvas completeness (6 methods from FR-14a)
3. Layout pass trigger (direct requestLayout vs. Choreographer integration)
4. focusSearch() implementation (stub vs. basic implementation)

Each open question includes context and a recommended resolution.

---

### P-09 -- Constitution principles are cited

**Result: PASS**

The "Constitution Compliance" table cites each principle with a specific decision:

| Principle | Specific Decision |
|-----------|------------------|
| I - Safety (enum class) | "All constants use enum class: Visibility, LayoutDirection, ViewFlags, ViewGroupFlags, DescendantFocusability." |
| I - Safety (std::span) | "No raw pointer arithmetic. Bounds-checked access via std::span." |
| I - Safety (RAII) | "All objects use smart pointers (std::shared_ptr for View ownership). No new/delete." |
| I - Safety (initialization) | "All fields have default values in the class definition." |
| I - Safety (std::expected/optional) | "std::optional<std::any> for getTag. std::expected where recoverable errors possible." |
| II - Zero-cost | "ViewParent/ViewManager via CRTP. No virtual dispatch." |
| III - TDD | "All tests written Red-Green-Refactor. Coverage target >80% per module." |
| IV - Spec as truth | "Every FR traces to a method, field, or test." |
| V - Tech Stack | "All dependencies documented in research.md." |

Each principle has a concrete, specific decision attached.

---

### P-10 -- No circular architecture

**Result: PASS**

Scanned layer descriptions for circular dependencies:

- ViewParentMixin (header-only template) is used by View and ViewGroup. No reverse dependency.
- ViewManagerMixin (header-only template) is used by View and ViewGroup. No reverse dependency.
- View is the base class; ViewGroup extends View. No reverse dependency.
- LayoutParams is a template parameter of ViewGroup. No reverse dependency.
- The dependency graph is strictly hierarchical: ViewParentMixin -> View -> ViewGroup. No cycles.

---

## data-model.md

### DM-01 -- Every entity has a primary key

**Result: FAIL**

**Location:** MeasureSpec entity  
**Found:** "packed: uint32_t, not null"  
**Problem:** MeasureSpec has no primary key or identifier field. While MeasureSpec is a value type (not an entity with identity), the check requires every entity to have a designated primary key with explicit type and generation strategy.  
**Fix:** Either designate `packed` as the primary key with a comment explaining it serves as the unique identifier for a measure specification, or reclassify MeasureSpec as a value type (not an entity) and remove it from the entity list.

**Location:** ViewParentMixin<Derived>, ViewManagerMixin<Derived> entities  
**Found:** "No state. Provides methods for parent-child communication."  
**Problem:** These are mixin classes with no state and no primary key. They are not entities in the data sense.  
**Fix:** Reclassify these as interface/mixin types rather than entities.

---

### DM-02 -- Every foreign key is named explicitly

**Result: FAIL**

**Location:** Relationships section  
**Found:** "ViewGroup has many View via children_ (owned, shared_ptr)."  
**Problem:** While `children_` is named, the relationship description for View belonging to ViewGroup via CRTP parent chain does not name a specific foreign key column. The parent reference is implicit through the CRTP mixin mechanism, not an explicit field.  
**Fix:** Explicitly state: "View's parent reference is established through ViewParentMixin<View>::m_parent (raw pointer, non-owning, set during addView)."

**Location:** Relationships section  
**Found:** "ViewGroup has many TLayoutParams via childParams_ (owned, shared_ptr, 1:1 with children_)."  
**Problem:** TLayoutParams is a template parameter, not a concrete type. The foreign key relationship is implicit through the 1:1 alignment with children_.  
**Fix:** Clarify: "childParams_[i] corresponds to children_[i] by index alignment."

---

### DM-03 -- Nullable fields are intentional

**Result: PASS**

Nullable fields and their justification:

| Field | Nullable | Justification |
|-------|----------|---------------|
| tag_ | nullable, default nullptr | "Arbitrary object associated with this view" -- tag may or may not be set |
| touchTarget_ | nullable, default nullptr | "The view that received the current ACTION_DOWN gesture" -- null when no gesture is active |

All nullable fields have explicit justification. Non-nullable fields are correctly marked as not null.

---

### DM-04 -- State machines are complete

**Result: FAIL**

**Location:** View entity state machine  
**Found:**
```
[unmeasured] --measure()--> [measured]
[unlaid-out] --layout()-->  [laid-out]
[not-drawn]  --draw()-->    [drawn]
```
**Problem:** The state machine is incomplete:
1. States are independent (no transitions between them). A View can be measured but not laid out, or laid out but not drawn. The state machine does not define valid state combinations or transitions between states.
2. No invalid transitions are identified (e.g., can you call draw() before measure()? Can you call layout() before measure()?).
3. No terminal or error states are defined.
4. The state machine does not account for GONE visibility affecting draw behavior (FR-12 says draw() returns early if GONE).
5. No state is listed for "layout requested but not completed" (FR-11).

**Fix:** Define a complete state machine with:
- All valid states: unmeasured, measured, unlaid-out, laid-out, not-drawn, drawn, layout-requested
- All valid transitions between states
- Invalid transitions (e.g., draw() before measure() should assert or produce undefined behavior)
- Terminal states (if any)
- GONE state interaction with draw

---

### DM-05 -- Indexes cover documented query patterns

**Result: PASS**

The data model explicitly states "Indexes: N/A (single View instance, no database)" for all entities. The plan's service layer describes query patterns (getChildAt, getChildCount, measureChildren, layoutChildren) which operate on in-memory std::vector collections, not database indexes. This is correct for the architecture.

---

### DM-06 -- No ambiguous type choices

**Result: FAIL**

**Location:** View entity, tag_ field  
**Found:** "tag_: std::any, nullable, default nullptr"  
**Problem:** `std::any` is used for tag storage, but the default value is `nullptr`. `std::any` cannot hold a nullptr by default -- it requires explicit construction. The default should be `std::nullopt` (via `std::optional<std::any>`) or an empty `std::any{}`. Storing a raw pointer default with an `std::any` type is a type mismatch.  
**Fix:** Either: (a) use `std::optional<std::any>` with default `std::nullopt`, or (b) use a raw pointer `void*` with default `nullptr`, or (c) use `std::any{}` as the default.

**Location:** View entity, flags_ field  
**Found:** "flags_: enum class ViewFlags : uint32_t, not null, default all clear"  
**Problem:** The default "all clear" is described in prose rather than specified as a concrete value. The enum class defines NONE = 0x00000000. The default should explicitly reference NONE.  
**Fix:** Change default to "NONE (0x00000000)" for clarity.

---

### DM-07 -- Many-to-many joins are explicit

**Result: PASS**

No many-to-many relationships exist in the data model:
- View to ViewGroup is one-to-many (one ViewGroup has many Views via children_).
- LayoutParams to View is one-to-one (per-child LayoutParams aligned 1:1 with children_).
- MarginLayoutParams extends LayoutParams via inheritance, not a join.

No join tables are needed.

---

### DM-08 -- Timestamps follow a consistent pattern

**Result: PASS**

No entities have `created_at` or `updated_at` timestamps. The View system is an in-memory C++ object model where timestamps are not applicable (no persistence, no database). This is consistent across all entities.

---

## tasks.md

**Result: FAIL (file does not exist)**

The file `tasks.md` does not exist at `.specify/specs/001-view-foundational/tasks.md`. All 10 task checks fail by absence.

| Check | Status |
|-------|--------|
| T-01 -- Every task has an exact file path | FAIL (no tasks) |
| T-02 -- Every task has an imperative title | FAIL (no tasks) |
| T-03 -- Acceptance criteria are commands or observables | FAIL (no tasks) |
| T-04 -- No task spans multiple layers | FAIL (no tasks) |
| T-05 -- Dependency chains are complete | FAIL (no tasks) |
| T-06 -- Every phase has a checkpoint | FAIL (no tasks) |
| T-07 -- Tests are tasks, not afterthoughts | FAIL (no tasks) |
| T-08 -- Parallel markers are conservative | FAIL (no tasks) |
| T-09 -- Task count is proportional to complexity | FAIL (no tasks) |
| T-10 -- Final checkpoint traces spec coverage | FAIL (no tasks) |

**Fix:** Create `tasks.md` with the full task breakdown. Given 53 functional requirements across 6 architectural layers (data, service, API, UI, testing, deployment), the task count should be substantially higher than 10. Each task should belong to a single layer, have exact file paths, imperative titles, and verifiable acceptance criteria.

---

## constitution.md

### C-01 -- Principles are actionable

**Result: PASS**

Every principle is specific enough that a developer can check whether a piece of code violates it:

| Principle | Actionable? | Example |
|-----------|-------------|---------|
| I - Safety | Yes | "enum class and strong types only. No primitive obsession." -- A reviewer can check every constant and parameter type. |
| I - Safety (5 dimensions) | Yes | Each dimension has a concrete rule (std::span, RAII, smart pointers, initialized, std::expected). |
| II - Zero-cost | Yes | "Static polymorphism over virtual functions." -- A reviewer can check for virtual dispatch. |
| III - TDD | Yes | "Red -> Green -> Refactor. Strictly in that order." -- A reviewer can check commit history for test-first ordering. |
| IV - Spec tracking | Yes | "Before starting: [ ] -> [~]. After completion: [~] -> [x] <sha>." -- A reviewer can check tasks.md. |
| V - Tech Stack | Yes | "Any new library... MUST be documented." -- A reviewer can check for undocumented dependencies. |

All principles are concrete and checkable.

---

### C-02 -- Principles are testable

**Result: PASS**

For each principle, a code reviewer can verify compliance without subjective judgment:

| Principle | Verifiable How? |
|-----------|----------------|
| I - enum class | Search code for non-enum-class constants. Binary: found or not found. |
| I - std::span | Search code for raw pointer arithmetic. Binary: found or not found. |
| I - RAII | Search code for new/delete. Binary: found or not found. |
| I - Initialization | Code review for uninitialized member reads. Binary: found or not found. |
| I - std::expected | Check error handling uses std::expected, not raw error codes. Binary: found or not found. |
| II - Zero-cost | Check for virtual dispatch on abstractions. Binary: found or not found. |
| III - TDD | Check commit history: test commits before implementation commits. Binary: order is correct or not. |
| IV - Spec tracking | Check tasks.md status markers match actual work. Binary: matches or not. |
| V - Tech Stack | Check for undocumented dependencies. Binary: documented or not. |

All principles are testable.

---

### C-03 -- No conflicting principles

**Result: PASS**

Scanned all principle pairs for conflicts:

| Principle Pair | Conflict? |
|---------------|-----------|
| I (Safety) vs II (Zero-cost) | No conflict. enum class and std::span have zero overhead. RAII via smart pointers has negligible overhead. |
| I (Safety) vs III (TDD) | No conflict. Tests can verify safety properties. |
| II (Zero-cost) vs III (TDD) | No conflict. Tests can verify zero-cost claims via benchmarking. |
| III (TDD) vs IV (Spec tracking) | No conflict. Both are workflow requirements. |
| IV (Spec tracking) vs V (Tech Stack) | No conflict. Both are documentation/governance requirements. |
| I (Safety) vs V (Tech Stack) | No conflict. Both constrain implementation choices. |

No conflicting pairs found.

---

### C-04 -- Principles cover the key risk areas

**Result: PASS**

All five key risk areas are addressed:

| Risk Area | Covered By | Details |
|-----------|-----------|---------|
| Code quality/style | Principle I, Code Quality section | enum class, std::span, namespaces, documentation, no performance regressions |
| Testing requirements | Principle III | Red-Green-Refactor, >80% coverage, GoogleTest/GoogleMock, Android CTS |
| Security baseline | Quality Gates section | "No security vulnerabilities" gate, bounds safety, input validation |
| Dependency management | Principle V, Dependency Management table | Documentation requirement, version table, rules for new dependencies |
| Performance expectations | Principle II, Code Quality section | Zero-cost abstractions, no performance regressions vs. CTS benchmarks |

All five areas are covered. Security is addressed in the Quality Gates rather than a dedicated principle, but it is present.

---

### C-05 -- Principles are scoped

**Result: PASS**

Each principle indicates its scope:

| Principle | Scope |
|-----------|-------|
| I - Safety | "Every component" (all components) |
| II - Zero-cost | "Every abstraction" (all abstractions) |
| III - TDD | "per module" (all modules with tests) |
| IV - Spec tracking | "All work tracked in .specify/specs/" (all feature work) |
| V - Tech Stack | "Any new library, language feature, or build tool" (all new dependencies) |

All principles have clear scope.

---

## Required Fixes (FAIL items)

These must be resolved before this artifact is used in the next pipeline phase:

### spec.md
1. **S-03** in `spec.md` -- US-06 criterion 1: replace "work correctly" with a specific, measurable condition
2. **S-03** in `spec.md` -- US-12 criterion 4: replace "as appropriate" with a specific z-order rule
3. **S-07** in `spec.md` -- Remove implementation language: C++23 references, std::any, class declaration syntax (FR-33), C++ enum syntax, namespace convention, file paths

### plan.md
4. **P-03** in `plan.md` -- Security model does not cover all three roles (Framework Developer, NDK Developer, Test Engineer) at the API layer

### data-model.md
5. **DM-01** in `data-model.md` -- MeasureSpec has no primary key; either designate `packed` as PK or reclassify as value type
6. **DM-01** in `data-model.md` -- ViewParentMixin and ViewManagerMixin have no state and no PK; reclassify as mixins, not entities
7. **DM-02** in `data-model.md` -- View-to-ViewGroup parent relationship via CRTP does not name an explicit foreign key column
8. **DM-04** in `data-model.md` -- View state machine is incomplete: independent states, no invalid transitions, no GONE handling, no layout-requested state
9. **DM-06** in `data-model.md` -- tag_ field type mismatch: std::any with default nullptr (std::any cannot hold nullptr by default)
10. **DM-06** in `data-model.md` -- flags_ default "all clear" is prose, not a concrete enum value (should be NONE = 0x00000000)

### tasks.md
11. **All T-checks** -- `tasks.md` does not exist. Create the file with full task breakdown before any implementation phase.

---

## Recommended Improvements (WARNING items)

These should be resolved; if deferred, note the assumption being made:

1. **S-07** in `spec.md` -- Consider moving constitutional implementation references (C++23, NDK, std::span, RAII) to a separate "Implementation Notes" section or the plan. The spec should remain tech-agnostic.

2. **P-03** in `plan.md` -- Security model could be more specific about role-based API permissions even for a library (public vs. protected vs. internal access).

3. **DM-02** in `data-model.md` -- The CRTP parent reference is a valid C++ design pattern but does not follow the traditional foreign key naming convention. Consider adding a comment like "parent reference: non-owning raw pointer, established via CRTP static_cast in addView()."

---

## Recommended Action

**Do not proceed to the next phase.** The checklist returns FAIL due to:
- 11 required fixes across spec.md, plan.md, and data-model.md
- tasks.md is entirely missing, blocking all task-level quality checks

**Priority order:**
1. Create `tasks.md` -- this is a blocking artifact for the pipeline
2. Fix S-03 (non-binary acceptance criteria) in spec.md
3. Fix S-07 (implementation language) in spec.md
4. Fix DM-04 (incomplete state machine) in data-model.md
5. Fix DM-06 (type mismatches) in data-model.md
6. Fix P-03 (role-based security) in plan.md

After fixes are applied, re-run this checklist in strict mode.
