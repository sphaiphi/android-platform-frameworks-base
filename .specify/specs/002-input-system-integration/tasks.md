# Tasks: Input System Integration (InputEventReceiver)

**Input**: Design documents from `specs/002-input-system-integration/`
**Prerequisites**: plan.md, spec.md, research.md, data-model.md, contracts/

**Tests**: TDD approach — write failing tests first, then implementation (per Constitution Principle III)

## Format: `- [ ] [ID] [P?] [Story] Description`

- **[P]**: Can run in parallel (different files, no dependencies on incomplete tasks)
- **[Story]**: Which user story this belongs to (US1, US2, US3, US4)
- Include exact file paths in descriptions

---

## Phase 1: Setup (Shared Infrastructure)

**Purpose**: Verify build infrastructure and CMake registration for new files

- [ ] T001 Verify CMake build compiles with existing View/ViewGroup/ViewRootImpl sources in core/cpp/CMakeLists.txt

---

## Phase 2: Foundational (Blocking Prerequisites)

**Purpose**: Core types and infrastructure that MUST be complete before ANY user story can be implemented

**⚠️ CRITICAL**: No user story work can begin until this phase is complete

- [ ] T002 Create `InputError` enum class in `core/cpp/include/android/view/InputEvent.h` with values: NO_EVENT_IN_PROGRESS, DISPOSED, TYPE_MISMATCH, SOCKET_READ_ERROR, SOCKET_WRITE_ERROR, INVALID_CHANNEL, WIRE_FORMAT_ERROR
- [ ] T003 [P] Create `InputEvent.h` header with `std::variant<MotionEvent, KeyEvent>` wrapper and `InputEventWrapper` struct holding `event` variant and `sequence_number` uint32_t in `core/cpp/include/android/view/InputEvent.h`
- [ ] T004 [P] Implement `InputEvent.cpp` with `InputEventWrapper` constructor and sequence number assignment logic in `core/cpp/src/android/view/InputEvent.cpp`
- [ ] T005 Create mock `InputChannel` helper for host tests in `core/cpp/tests/mock_input_channel.h` — provides fake valid channel with controllable socket pair for injecting synthetic events
- [ ] T006 [P] Extend `MotionEvent.h` with additional fields: `device_id`, `source`, `history_size`, `history` vector, `event_time`, `pointer_count`, `pointer_ids`, `pointer_coords`; add constructor overloads for full event creation
- [ ] T007 [P] Extend `KeyEvent.h` with additional fields: `device_id`, `source`, `event_time`, `repeat_count`, `meta_state`; add constructor overloads
- [ ] T008 [P] Extend `MotionEvent.cpp` with implementations for new fields and `offset_location()` with history buffer support
- [ ] T009 [P] Extend `KeyEvent.cpp` with implementations for new fields
- [ ] T010 [P] Extend `InputChannel.h` with `read_fd()` accessor returning native FD as int, and `write_fd()` accessor; add `close()` method declaration
- [ ] T011 [P] Extend `InputChannel.cpp` with `read_fd()`, `write_fd()`, and `close()` implementations using existing `native_handle_` void* cast to int

**Checkpoint**: Foundation ready — all shared types, mocks, and extensions in place. User story implementation can now begin.

---

## Phase 3: User Story 1 - Receive and Dispatch Touch Events (Priority: P1) 🎯 MVP

**Goal**: Implement `InputEventReceiver` core: wire format parsing, event callback dispatch, and `finishInputEvent()` completion signaling.

**Independent Test**: Create an `InputEventReceiver` bound to a mock `InputChannel`, inject a synthetic `MotionEvent` through the socket, verify `onInputEvent()` is called with correct event data, then verify `finishInputEvent()` sends handled status back.

### Implementation for User Story 1

- [ ] T012 [P] [US1] Rewrite `InputEventReceiver.h` header: replace stub with full class declaration including private fields (`mChannel`, `mLooper`, `mCurrentEvent`, `mSequenceCounter`, `mDisposed`, `mFdWatcherRegistered`), public methods (`consumeEvents`, `finishInputEvent`, `dispose`, `onFocusEvent`, `onTouchModeChanged`, `consumeBatchedInputEvents`, `probablyHasInput`, `reportTimeline`), and pure virtual `onInputEvent(std::variant<MotionEvent, KeyEvent>)`
- [ ] T013 [US1] Implement `InputEventReceiver.cpp` constructor: validate channel is valid, looper is non-null, set `mDisposed=false`, `mSequenceCounter=0`, `mCurrentEvent` empty, do NOT register FD watcher yet (deferred to US2)
- [ ] T014 [US1] Implement `InputEventReceiver.cpp::consumeEvents()`: read all available bytes from input channel FD using `read()` in a loop, parse Android `InputEvent` wire protocol (8-byte header: sequence number, event type, action, device ID, source, history size; followed by type-specific payload), construct `std::variant<MotionEvent, KeyEvent>` for each parsed event, return `std::vector<std::variant<...>>`
- [ ] T015 [US1] Implement `InputEventReceiver.cpp::finishInputEvent()`: validate `mCurrentEvent.has_value()`, validate event type matches, write `handled` status to `InputChannel` write FD via wire protocol, reset `mCurrentEvent`, return `std::expected<void, InputError>`
- [ ] T016 [US1] Implement `InputEventReceiver.cpp::dispose()`: set `mDisposed=true`, close `InputChannel`, no-op remaining methods after dispose
- [ ] T017 [US1] Implement `InputEventReceiver.cpp::onFocusEvent()`, `onTouchModeChanged()`: state tracking stubs (set internal bool flags, no view propagation yet — US4)
- [ ] T018 [US1] Implement `InputEventReceiver.cpp::consumeBatchedInputEvents()`: call `consumeEvents()` and dispatch all returned events, return `true` if any events were consumed
- [ ] T019 [US1] Implement `InputEventReceiver.cpp::probablyHasInput()`: check if data is available on the read FD using `poll()` with `POLLPRI` timeout of 0, return `true` if data available (may return false negatives)
- [ ] T020 [US1] Implement `InputEventReceiver.cpp::reportTimeline()`: no-op stub for now (latency reporting out of scope)
- [ ] T021 [US1] Write `input_event_receiver_test.cpp`: tests for constructor validation, `consumeEvents()` parsing of wire format, `finishInputEvent()` success and error paths, `dispose()` state transitions, sequential event processing invariant, `probablyHasInput()` behavior
- [ ] T022 [US1] Write `input_event_test.cpp`: tests for `InputEventWrapper` construction, `std::variant` type holding, sequence number assignment

**Checkpoint**: User Story 1 complete — `InputEventReceiver` can receive events from socket, parse wire format, deliver callbacks, and signal completion.

---

## Phase 4: User Story 2 - Event Reception via Looper Polling (Priority: P1)

**Goal**: Integrate `InputEventReceiver` with `Looper` FD watcher for asynchronous event reception. Events wake the Looper when available on the socket.

**Independent Test**: Create a receiver, register it with a Looper, write data to the write-end of the `InputChannel` socket pair from another thread, verify the Looper callback fires and `onInputEvent` is invoked.

### Implementation for User Story 2

- [ ] T023 [US2] Extend `InputEventReceiver.cpp` with FD watcher registration: add `registerWithLooper()` method that registers the input channel read FD with the `Looper` using a callback that invokes `consumeEvents()` and dispatches each event via `onInputEvent()`. Registration happens in constructor after validation.
- [ ] T024 [US2] Implement Looper callback mechanism: the FD watcher callback reads from the FD, calls `consumeEvents()`, iterates the returned vector, sets `mCurrentEvent` for each event, invokes `onInputEvent()`, and waits for `finishInputEvent()` before processing the next event (sequential invariant)
- [ ] T025 [US2] Implement `dispose()` FD cleanup: unregister FD watcher from Looper before closing channel (extend T016 implementation)
- [ ] T026 [US2] Write `input_event_receiver_test.cpp` extensions: tests for Looper FD registration, socket write triggering Looper callback, multiple events in batch, dispose removing FD watcher
- [ ] T027 [US2] Extend `InputChannel.cpp` with `sendHandled(bool handled)` method: writes the handled status byte to the write-end FD using `write()`

**Checkpoint**: User Story 2 complete — events asynchronously wake the Looper, are parsed, and dispatched via callbacks.

---

## Phase 5: User Story 3 - Event Dispatch Through View Hierarchy (Priority: P2)

**Goal**: Implement `ViewGroup.dispatchPointerEvent()` with hit-testing, coordinate transformation, event interception, and reverse Z-order child iteration. Add `ViewRootImpl` stub for input dispatch.

**Independent Test**: Construct a `View`/`ViewGroup` hierarchy, feed a `MotionEvent` through `ViewRootImpl`'s dispatch path, verify the correct view receives the event with transformed coordinates.

### Implementation for User Story 3

- [ ] T028 [P] [US3] Extend `ViewGroup.h`: add `dispatch_pointer_event(const MotionEvent& event)` method declaration, `on_intercept_touch_event(const MotionEvent& event)` virtual method, `get_children()` accessor for child iteration, `bounds_overlap(float x, float y)` helper
- [ ] T029 [US3] Implement `ViewGroup.cpp::dispatch_pointer_event()`: check `on_intercept_touch_event()` — if true, dispatch to this group's `on_touch_event()`; otherwise iterate children in reverse order (top-most first), for each child check if coordinates fall within bounds using `get_left()`, `get_top()`, `get_right()`, `get_bottom()`, transform coordinates via `offset_location()` on a copy of the event, recursively call `child->dispatch_pointer_event()`, return `true` if any child handled the event
- [ ] T030 [US3] Implement `ViewGroup.cpp::on_intercept_touch_event()`: default returns `false`
- [ ] T031 [US3] Extend `View.h`: add `dispatch_pointer_event(const MotionEvent& event)` declaration that delegates to `dispatch_touch_event()`, add `on_touch_event(const MotionEvent& event)` declaration
- [ ] T032 [US3] Implement `View.cpp::dispatch_pointer_event()`: call `dispatch_touch_event(event)`, return `true` if handled
- [ ] T033 [US3] Extend `ViewRootImpl.h`: add `dispatch_pointer_event(const MotionEvent& event)` method that forwards to `view_->dispatch_pointer_event(event)` if `view_` is set
- [ ] T034 [US3] Implement `ViewRootImpl.cpp::dispatch_pointer_event()`: forward to `view_->dispatch_pointer_event(event)`, return the handled status
- [ ] T035 [US3] Write `view_group_dispatch_test.cpp`: tests for hit-testing within child bounds, coordinate transformation to local space, event interception via `on_intercept_touch_event()`, reverse Z-order iteration, nested hierarchy recursion, event bubbling when no child handles
- [ ] T036 [US3] Write `view_root_impl_input_test.cpp`: tests for `dispatch_pointer_event()` forwarding to root view, null view handling

**Checkpoint**: User Story 3 complete — touch events flow from `ViewRootImpl` through `ViewGroup` hit-testing to leaf `View` with proper coordinate transformation and interception.

---

## Phase 6: User Story 4 - Special Event Handling (Priority: P3)

**Goal**: Implement non-motion event callbacks: `onFocusEvent`, `onTouchModeChanged`, `onPointerCaptureEvent`. Propagate focus/touch mode state to associated view.

**Independent Test**: Invoke each callback method directly and verify the correct internal state is updated.

### Implementation for User Story 4

- [ ] T037 [US4] Extend `InputEventReceiver.cpp::onFocusEvent(bool hasFocus)`: store focus state, if `view_` is available via `ViewRootImpl` stub, call `view_->set_focused(hasFocus)` or equivalent
- [ ] T038 [US4] Extend `InputEventReceiver.cpp::onTouchModeChanged(bool inTouchMode)`: store touch mode state
- [ ] T039 [US4] Add `onPointerCaptureEvent(bool enabled)` stub to `InputEventReceiver.h` and `.cpp` (no-op for now, tracks pointer capture state)
- [ ] T040 [US4] Write `input_event_receiver_test.cpp` extensions: tests for `onFocusEvent` state propagation, `onTouchModeChanged` state update, `onPointerCaptureEvent` stub behavior

**Checkpoint**: User Story 4 complete — special event callbacks update state and propagate to views.

---

## Phase 7: Polish & Cross-Cutting Concerns

**Purpose**: Build integration, coverage, and validation

- [ ] T041 Update `core/cpp/CMakeLists.txt`: add `InputEvent.cpp`, `InputEventReceiver.cpp` to `CORE_SOURCES`; add `input_event_test.cpp`, `input_event_receiver_test.cpp`, `view_group_dispatch_test.cpp`, `view_root_impl_input_test.cpp` to test targets
- [ ] T042 Update `core/cpp/CMakeLists.txt`: add `MotionEvent.cpp`, `KeyEvent.cpp`, `ViewGroup.cpp`, `ViewRootImpl.cpp`, `InputChannel.cpp` if not already present
- [ ] T043 Build and run all tests: `cmake -B build -S core/cpp && cmake --build build && cd build && ctest --output-on-failure`
- [ ] T044 Verify code coverage >80% for all new/modified files using `gcov`/`lcov`
- [ ] T045 Run quickstart.md examples: verify all code snippets compile and tests pass
- [ ] T046 Static analysis: verify no `-Wextra` or `-Wpedantic` warnings on new code with `-Wall -Wextra -Werror -Wpedantic`

---

## Dependencies & Execution Order

### Phase Dependencies

- **Setup (Phase 1)**: No dependencies — can start immediately
- **Foundational (Phase 2)**: Depends on Setup completion — BLOCKS all user stories
- **User Stories (Phase 3-6)**: All depend on Foundational phase completion
  - US1 and US2 are both P1 and can theoretically run in parallel, but US2 depends on US1's `InputEventReceiver` class existing
  - US3 depends on US1 (needs `MotionEvent` variant type) and existing `ViewGroup`/`View`
  - US4 depends on US1 (needs `InputEventReceiver` base)
- **Polish (Phase 7)**: Depends on all desired user stories being complete

### User Story Dependencies

- **US1 (P1)**: Can start after Foundational (Phase 2) — no dependencies on other stories. **MVP scope.**
- **US2 (P1)**: Can start after Foundational + US1 (needs `InputEventReceiver` class from US1)
- **US3 (P2)**: Can start after Foundational + US1 (needs `MotionEvent` type from US1/Phase 2)
- **US4 (P3)**: Can start after Foundational + US1 (needs `InputEventReceiver` class from US1)

### Within Each User Story

- Models/extensions before services/dispatch
- Implementation before tests (write tests first, confirm they fail, then implement)
- Story complete before moving to next priority

### Parallel Opportunities

- Phase 2 tasks T003-T011: All [P] tasks can run in parallel (different files, no cross-dependencies)
- Phase 3 tasks T012-T022: T012 (header) must precede T013-T020 (implementations); T021-T022 (tests) can start after T012
- Phase 5 tasks T028-T036: T028 (ViewGroup header) and T031 (View header) can run in parallel; implementations depend on headers

---

## Implementation Strategy

### MVP First (User Story 1 Only)

1. Complete Phase 1: Setup
2. Complete Phase 2: Foundational (CRITICAL — blocks all stories)
3. Complete Phase 3: User Story 1
4. **STOP and VALIDATE**: Build and run all US1 tests independently
5. Demo: synthetic socket event → `onInputEvent` callback → `finishInputEvent`

### Incremental Delivery

1. Complete Setup + Foundational → Foundation ready
2. Add US1 → Test independently → Core input path works (MVP!)
3. Add US2 → Test independently → Async Looper integration works
4. Add US3 → Test independently → Full view hierarchy dispatch works
5. Add US4 → Test independently → Special events work
6. Polish → Build verification, coverage, static analysis

---

## Notes

- [P] tasks = different files, no dependencies
- [Story] label maps task to specific user story for traceability
- Each user story should be independently completable and testable
- Write failing tests first (TDD: Red → Green → Refactor)
- Commit after each task or logical group
- Stop at any checkpoint to validate story independently
