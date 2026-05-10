# Plan: Complete Windowing IPC Track (Phase 4 finalization + Phase 5)

## Context

The windowing_ipc_20260502 track is 3/5 phases complete. Phase 4's implementation work (finishDrawing tests + ViewRootImpl integration) is done and committed, but the plan.md and learnings haven't been finalized yet. Phase 5 (CTS validation) remains.

## Current State

**Completed:**
- Phase 1: AIDL Generation & Skeleton (`f94c4553`, checkpoint `038fdd21`)
- Phase 2: Window Registration (`e7c21715`, checkpoint `e7c21715`)
- Phase 3: Layout & Surface Negotiation (`ca9ffa52`, checkpoint `ca9ffa52`)
- Phase 4 Task 1: finishDrawing tests (`45f4f7f8`)
- Phase 4 Task 2: ViewRootImpl integration (`cef5c8c8`)

**Tests:** 363 passed, 0 failed

**Remaining:**
- Phase 4: Finalize plan.md (mark tasks complete, add checkpoint)
- Phase 5: Port windowing CTS tests

## Steps

1. **Finalize Phase 4 plan.md** — mark tasks as complete, add checkpoint commit
2. **Phase 5: Port windowing CTS tests**
   - Identify CTS tests from `cts/java/android/view/cts` related to windowing/IWindowSession
   - Port to C++ GoogleTest in `cts/cpp/tests/`
   - Build and run CTS tests
3. **Finalize track** — mark track complete, archive

## Key Files

- `conductor/tracks/windowing_ipc_20260502/plan.md`
- `conductor/tracks/windowing_ipc_20260502/learnings.md`
- `core/cpp/tests/IWindowSession_test.cpp`
- `core/cpp/tests/ViewRootImpl_test.cpp`
- `core/cpp/src/android/view/WindowSession.cpp`
- `core/cpp/src/android/view/ViewRootImpl.cpp`

## Verification

```bash
cd build && ctest --output-on-failure
```
