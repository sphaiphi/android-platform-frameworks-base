# Track Learnings: rendering_primitives_20260426

Patterns, gotchas, and context discovered during implementation.

## Codebase Patterns (Inherited)

- Canvas is currently a pure interface with a single `draw_rect` method — will be replaced/extended with a command-recording implementation
- RenderNode already references Canvas via `begin_recording()` — must maintain compatibility
- Rect class is complete and well-tested — Path and Canvas should reuse it for bounds operations
- View::on_draw() is a no-op stub — primary consumer of this work
- All C++ code follows `android::graphics` namespace convention

---

<!-- Learnings from implementation will be appended below -->

## [2026-04-30] - Phase 1: Color
- **Implemented:** Color.h, Color.cpp with full static API
- **Files changed:** Color.h, Color.cpp, Color_test.cpp, CMakeLists.txt (x2)
- **Commit:** 9054cca1
- **Learnings:**
  - `setAlphaColor` takes `uint32_t color` not `uint8_t` — matches Android API where color is a packed 32-bit value
  - `expected_shim.h` provides `std::expected` for the shim build
  - Color is purely static — no instance state, all utility methods
---

## [2026-04-30] - Phase 2: Paint
- **Implemented:** Paint.h, Paint.cpp with style, color, alpha, stroke, text, flags
- **Files changed:** Paint.h, Paint.cpp, Paint_test.cpp, CMakeLists.txt (x2)
- **Commit:** d700aa96
- **Learnings:**
  - Nested enum classes need `Paint::Style` prefix in .cpp return types
  - 16 tests cover all Paint properties
---

## [2026-04-30] - Phase 3: Path
- **Implemented:** Path.h, Path.cpp with variant-based element storage
- **Files changed:** Path.h, Path.cpp, Path_test.cpp, CMakeLists.txt (x2)
- **Commit:** 05f2bc2f
- **Learnings:**
  - `std::variant` works well for command/element storage — each path op is a distinct struct
  - `computeBounds()` uses `std::visit` with `if constexpr` to handle variant types
  - Path includes Rect.h for bounds computation
---

## [2026-04-30] - Phase 4: Canvas
- **Implemented:** Canvas.h, Canvas.cpp command-recording class
- **Files changed:** Canvas.h, Canvas.cpp, Canvas_test.cpp, CMakeLists.txt (x2), ViewRootImpl.cpp, Drawing_test.cpp
- **Commit:** 64559954
- **Learnings:**
  - Canvas was a pure interface; replaced with concrete class keeping virtual draw_rect() for RenderNode compat
  - HostCanvas and MockCanvas subclasses needed constructor update for Canvas(width, height)
  - Variant-based Command list enables full test inspection of draw calls
  - Canvas includes Path.h (not forward-declared) since Path is stored by value in variant
---

## [2026-04-30] - Phase 5: Drawable + ColorDrawable
- **Implemented:** Drawable.h, Drawable.cpp, ColorDrawable.h, ColorDrawable.cpp
- **Files changed:** Drawable.h, Drawable.cpp, ColorDrawable.h, ColorDrawable.cpp, Drawable_test.cpp, CMakeLists.txt (x2)
- **Commit:** d1410cbf
- **Learnings:**
  - Drawable is abstract with pure virtual draw(Canvas*)
  - ColorDrawable overrides getIntrinsicWidth/Height to return 0 (base returns -1)
  - ColorDrawable composites alpha from both drawable alpha and color alpha
---

## [2026-04-30] - Phase 6: Integration
- **Implemented:** View::set_background(), View::get_background(), updated View::draw()
- **Files changed:** View.h, View.cpp, ViewRendering_test.cpp, CMakeLists.txt
- **Commit:** 5c2533ea
- **Learnings:**
  - View::draw() skips GONE views entirely (no draw commands produced)
  - Background Drawable draws before on_draw() call, matching Android behavior
  - Integration tests verify end-to-end: View → Canvas → Command list
---
