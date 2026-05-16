---

description: "Task list for WindowManager implementation"
---

# Tasks: WindowManager

**Input**: Design documents from `/specs/001-window-manager/`
**Prerequisites**: plan.md (required), spec.md (required for user stories), research.md, data-model.md, contracts/

**Tests**: TDD approach required by project constitution. Tests written first (Red phase), then implementation (Green phase).

**Organization**: Tasks are grouped by user story to enable independent implementation and testing of each story.

## Format: `[ID] [P?] [Story] Description`

- **[P]**: Can run in parallel (different files, no dependencies)
- **[Story]**: Which user story this task belongs to (e.g., US1, US2, US3, US4)
- Include exact file paths in descriptions

## Path Conventions

- **Single project**: `core/cpp/include/`, `core/cpp/src/`, `core/cpp/tests/` at repository root

## Phase 1: Setup (Shared Infrastructure)

**Purpose**: No additional setup needed — project structure already exists per plan.

## Phase 2: Foundational (Blocking Prerequisites)

**Purpose**: Core header declarations that ALL user stories depend on. No user story implementation can begin until these are complete.

**⚠️ CRITICAL**: No user story work can begin until this phase is complete

- [x] T001 Expand WindowManager.h header with public API declarations (addView, updateViewLayout, removeView, getDefaultDisplay) in core/cpp/include/android/view/WindowManager.h
- [x] T002 [P] Create WindowLayoutParams.h extending LayoutParams with window-specific fields (type, flags, format, gravity, x, y, alpha) in core/cpp/include/android/view/WindowLayoutParams.h
- [x] T003 [P] Create WindowManagerGlobal.h singleton tracker with internal addView/updateViewLayout/removeView/findView methods in core/cpp/include/android/view/WindowManagerGlobal.h
- [x] T004 [P] Create WindowManagerImpl.h delegator implementation with per-display DisplayInfo member in core/cpp/include/android/view/WindowManagerImpl.h

**Checkpoint**: Foundation ready - user story implementation can now begin in parallel

---

## Phase 3: User Story 1 - Add a View to a Window (Priority: P1) 🎯 MVP

**Goal**: Implement addView() so NDK developers can display a View on screen by creating a ViewRootImpl, registering with IWindowSession, and triggering the measure/layout/draw cycle.

**Independent Test**: A developer can create a View, construct a WindowManagerImpl, call addView() with WindowLayoutParams, and verify the view is registered and traversed.

### Tests for User Story 1 (OPTIONAL - only if tests requested) ⚠️

> **NOTE: Write these tests FIRST, ensure they FAIL before implementation**

- [x] T005 [P] [US1] Write failing test for WindowManager::addView success path in core/cpp/tests/WindowManager_test.cpp
- [x] T006 [P] [US1] Write failing test for WindowManager::addView duplicate view rejection in core/cpp/tests/WindowManager_test.cpp

### Implementation for User Story 1

- [x] T007 [US1] Implement WindowLayoutParams constructor and field accessors in core/cpp/src/android/view/WindowLayoutParams.cpp
- [x] T008 [US1] Implement WindowManager::addView() delegating to WindowManagerGlobal::addView() in core/cpp/src/android/view/WindowManager.cpp
- [x] T009 [US1] Implement WindowManagerGlobal::addView() creating ViewRootImpl, calling set_view(), and storing registration in core/cpp/src/android/view/WindowManagerGlobal.cpp
- [x] T010 [US1] Implement WindowManagerImpl constructor and delegator methods in core/cpp/src/android/view/WindowManagerImpl.cpp

**Checkpoint**: At this point, User Story 1 should be fully functional and testable independently

---

## Phase 4: User Story 2 - Update a View's Layout (Priority: P1)

**Goal**: Implement updateViewLayout() so developers can change a view's size, position, or window type after it has been added, triggering re-measure/layout/draw.

**Independent Test**: A developer adds a view, calls updateViewLayout() with new dimensions, and verifies the viewRootImpl performs a traversal with updated params.

### Tests for User Story 2 (OPTIONAL - only if tests requested) ⚠️

- [x] T011 [P] [US2] Write failing test for WindowManager::updateViewLayout success path in core/cpp/tests/WindowManager_test.cpp
- [x] T012 [P] [US2] Write failing test for WindowManager::updateViewLayout rejection when view not attached in core/cpp/tests/WindowManager_test.cpp

### Implementation for User Story 2

- [x] T013 [US2] Implement WindowManager::updateViewLayout() delegating to WindowManagerGlobal in core/cpp/src/android/view/WindowManager.cpp
- [x] T014 [US2] Implement WindowManagerGlobal::updateViewLayout() with findView validation and ViewRootImpl traversal in core/cpp/src/android/view/WindowManagerGlobal.cpp

**Checkpoint**: At this point, User Stories 1 AND 2 should both work independently

---

## Phase 5: User Story 3 - Remove a View from a Window (Priority: P1)

**Goal**: Implement removeView() so developers can tear down a view, release its ViewRootImpl, and stop rendering.

**Independent Test**: A developer adds a view, removes it, and verifies the view is unregistered and ViewRootImpl is destroyed.

### Tests for User Story 3 (OPTIONAL - only if tests requested) ⚠️

- [x] T015 [P] [US3] Write failing test for WindowManager::removeView success path in core/cpp/tests/WindowManager_test.cpp
- [x] T016 [P] [US3] Write failing test for WindowManager::removeView rejection when view not attached in core/cpp/tests/WindowManager_test.cpp

### Implementation for User Story 3

- [x] T017 [US3] Implement WindowManager::removeView() delegating to WindowManagerGlobal in core/cpp/src/android/view/WindowManager.cpp
- [x] T018 [US3] Implement WindowManagerGlobal::removeView() with IWindowSession::remove() call and cleanup in core/cpp/src/android/view/WindowManagerGlobal.cpp

**Checkpoint**: All user stories should now be independently functional

---

## Phase 6: User Story 4 - Query Display Information (Priority: P2)

**Goal**: Implement getDefaultDisplay() so developers can query display characteristics (size, density, rotation).

**Independent Test**: A developer constructs a WindowManagerImpl with a DisplayInfo and calls getDefaultDisplay() to verify it returns the correct values.

### Tests for User Story 4 (OPTIONAL - only if tests requested) ⚠️

- [x] T019 [P] [US4] Write failing test for WindowManager::getDefaultDisplay() returning correct DisplayInfo in core/cpp/tests/WindowManager_test.cpp

### Implementation for User Story 4

- [x] T020 [US4] Implement WindowManager::getDefaultDisplay() returning mDisplay in core/cpp/src/android/view/WindowManager.cpp

---

## Phase N: Polish & Cross-Cutting Concerns

**Purpose**: Improvements that affect all user stories

- [ ] T021 [P] Update CMakeLists.txt to include new WindowManager source files and test files in core/cpp/
- [ ] T022 [P] Run full host build (cmake --build build) and verify compilation in core/cpp/
- [ ] T023 Run all WindowManager unit tests via ctest -R WindowManager and verify all pass
- [ ] T024 Validate quickstart.md example compiles and runs correctly

---

## Dependencies & Execution Order

### Phase Dependencies

- **Setup (Phase 1)**: No dependencies - skipped (project structure exists)
- **Foundational (Phase 2)**: No dependencies - create all headers first (T001-T004)
- **User Stories (Phase 3-6)**: All depend on Foundational phase completion (T001-T004)
  - User stories can proceed sequentially in priority order (US1 → US2 → US3 → US4)
- **Polish (Final Phase)**: Depends on all desired user stories being complete

### User Story Dependencies

- **User Story 1 (P1)**: Can start after Foundational (Phase 2) - MVP, no dependencies on other stories
- **User Story 2 (P2)**: Depends on US1 (updateViewLayout requires addView to have been called)
- **User Story 3 (P3)**: Depends on US1 (removeView requires addView to have been called)
- **User Story 4 (P2)**: Independent of US1-3, can start after Foundational

### Within Each User Story

- Tests MUST be written and FAIL before implementation (TDD, per constitution Principle III)
- Headers before implementations
- Implementation before integration
- Story complete before moving to next priority

### Parallel Opportunities

- T002, T003, T004 (Foundational headers) can run in parallel
- T005, T006 (US1 tests) can run in parallel
- T011, T012 (US2 tests) can run in parallel
- T015, T016 (US3 tests) can run in parallel
- T019 (US4 test) is single task
- T021, T022 (Polish) can run in parallel

---

## Parallel Example: Foundational Phase

```bash
# Launch all header tasks together:
Task: "Create WindowLayoutParams.h in core/cpp/include/android/view/WindowLayoutParams.h"
Task: "Create WindowManagerGlobal.h in core/cpp/include/android/view/WindowManagerGlobal.h"
Task: "Create WindowManagerImpl.h in core/cpp/include/android/view/WindowManagerImpl.h"
```

---

## Implementation Strategy

### MVP First (User Story 1 Only)

1. Complete Phase 2: Foundational headers (T001-T004)
2. Complete Phase 3: User Story 1 - addView (T005-T010)
3. **STOP and VALIDATE**: Test addView independently
4. Build and run tests if ready

### Incremental Delivery

1. Complete Foundational (T001-T004) → Headers ready
2. Add User Story 1 (T005-T010) → Test addView independently → MVP!
3. Add User Story 2 (T011-T014) → Test updateViewLayout independently
4. Add User Story 3 (T015-T018) → Test removeView independently
5. Add User Story 4 (T019-T020) → Test getDefaultDisplay independently
6. Polish (T021-T024) → Build, test, validate

### Parallel Team Strategy

With multiple developers:

1. Team completes Foundational together (T001-T004)
2. Once Foundational is done:
   - Developer A: User Story 1 (addView)
   - Developer B: User Story 4 (display query) - independent of US1
3. After US1 + US4:
   - Developer A: User Story 2 (updateViewLayout)
   - Developer B: User Story 3 (removeView)

---

## Notes

- [P] tasks = different files, no dependencies
- [Story] label maps task to specific user story for traceability
- Each user story should be independently completable and testable
- Verify tests fail before implementing (TDD constitution requirement)
- Commit after each task or logical group
- Stop at any checkpoint to validate story independently
- Avoid: vague tasks, same file conflicts, cross-story dependencies that break independence
