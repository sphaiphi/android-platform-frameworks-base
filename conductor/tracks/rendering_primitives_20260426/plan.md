# Implementation Plan — Rendering Primitives

## Phase 1: Color [checkpoint: ab682a3d]
- [x] Task: Write Color unit tests (factory methods, accessors, constants, parseColor) [9054cca1]
- [x] Task: Implement Color class [9054cca1]
- [ ] Task: Implement Color class
- [ ] Task: Conductor - User Manual Verification 'Color' (Protocol in workflow.md)

## Phase 2: Paint [checkpoint: 396af3ad]
- [x] Task: Write Paint unit tests (style, color, alpha, stroke, text, flags) [d700aa96]
- [x] Task: Implement Paint class [d700aa96]
- [ ] Task: Conductor - User Manual Verification 'Paint' (Protocol in workflow.md)

## Phase 3: Path
- [x] Task: Write Path unit tests (point ops, shape ops, fill type, bounds) [05f2bc2f]
- [x] Task: Implement Path class [05f2bc2f]
- [ ] Task: Conductor - User Manual Verification 'Path' (Protocol in workflow.md)

## Phase 4: Canvas
- [ ] Task: Write Canvas unit tests (draw methods, save/restore, transform, clip)
- [ ] Task: Implement Canvas command-recording class
- [ ] Task: Conductor - User Manual Verification 'Canvas' (Protocol in workflow.md)

## Phase 5: Drawable + ColorDrawable
- [ ] Task: Write Drawable base class tests (bounds, intrinsic size, state, alpha)
- [ ] Task: Implement Drawable abstract base class
- [ ] Task: Write ColorDrawable tests
- [ ] Task: Implement ColorDrawable class
- [ ] Task: Conductor - User Manual Verification 'Drawable + ColorDrawable' (Protocol in workflow.md)

## Phase 6: Integration
- [ ] Task: Implement View::on_draw() to use Canvas + Drawable
- [ ] Task: Write integration test: View with ColorDrawable produces correct draw commands
- [ ] Task: Conductor - User Manual Verification 'Integration' (Protocol in workflow.md)
