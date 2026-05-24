# Specification — Rendering Primitives (Drawable, Paint, Canvas, Color, Path)

## Overview
Implement the foundational rendering primitive classes for the Android View system in C++23. This track provides the drawing infrastructure that `View::on_draw()`, `TextView`, and all UI widgets depend on to actually render content. Currently `on_draw()` is a no-op and Canvas is a 1-method stub — this track fills that gap.

## Functional Requirements

### Color (`android::graphics::Color`)
- Static factory methods: `argb()`, `rgb()`, `parseColor()` (hex string)
- Component accessors: `getRed()`, `getGreen()`, `getBlue()`, `getAlpha()`
- Manipulation: `setColorAlpha()`, `setAlphaColor()`
- Common constants: `BLACK`, `WHITE`, `RED`, `GREEN`, `BLUE`, `CYAN`, `MAGENTA`, `YELLOW`, `TRANSPARENT`, `LEGACY_BLACK`
- `toArgbString()` formatting

### Paint (`android::graphics::Paint`)
- Style: `Style` enum (FILL, STROKE, FILL_AND_STROKE) with getter/setter
- Color and alpha: `setColor()`, `getColor()`, `setAlpha()`, `getAlpha()`
- Stroke: `setStrokeWidth()`, `getStrokeWidth()`, `setStrokeCap()`, `setStrokeJoin()`, `setStrokeMiter()`
- Text: `setTextSize()`, `getTextSize()`, `measureText()`
- Flags: `setAntiAlias()`, `setDither()`, `setFilterBitmap()`
- `getTypeface()` / `setTypeface()` (handle typeface reference)
- TextAlign enum with getter/setter

### Path (`android::graphics::Path`)
- Point operations: `moveTo()`, `lineTo()`, `close()`, `reset()`, `rewind()`
- Shape operations: `addRect()`, `addCircle()`, `addOval()`, `addArc()`, `arcTo()`
- Path style: `FillType` enum (WINDING, EVEN_ODD, INVERSE_WINDING, INVERSE_EVEN_ODD) with getter/setter
- `isEmpty()`, `computeBounds()`

### Canvas (`android::graphics::Canvas`)
- Drawing: `drawRect()`, `drawCircle()`, `drawLine()`, `drawPath()`, `drawText()`, `drawDrawable()`
- State management: `save()`, `restore()`, `saveLayer()`, `getSaveCount()`
- Transform: `translate()`, `scale()`, `rotate()`, `translateAndScale()`
- Clipping: `clipRect()`, `clipPath()`
- Clear: `drawColor()` (fill entire canvas)
- Command-recording model: Canvas records draw calls into an internal command list for RenderNode replay

### Drawable (`android::graphics::Drawable`)
- Abstract base class
- `draw(Canvas*)` — pure virtual
- Bounds: `setBounds()`, `getBounds()`, `setBoundsInPlace()`
- Intrinsic size: `getIntrinsicWidth()`, `getIntrinsicHeight()` (default -1)
- State: `setState()`, `getState()`, `getMinimumHeight()`, `getMinimumWidth()`
- Appearance: `setAlpha()`, `getAlpha()`, `setColorFilter()`
- Level: `setLevel()`, `getLevel()`

### ColorDrawable (`android::graphics::ColorDrawable`)
- Concrete Drawable implementation rendering a solid color rectangle
- Constructor accepts Color value
- `draw()` delegates to `Canvas::drawRect()` with Paint configured to the color
- Intrinsic size returns 0 (fills bounds)

## Non-Functional Requirements
- **C++23 modernity**: `std::expected` for error returns (e.g., `parseColor`), strong-typed enums, `[[nodiscard]]`
- **Command pattern**: Canvas uses a variant-based command list for recording; zero hardware dependency
- **API parity**: Method naming and signatures mirror Android Java `android.graphics` classes
- **Testability**: All classes testable on host build without hardware GPU

## Acceptance Criteria
1. `Color::parseColor()` correctly parses `#RRGGBB`, `#AARRGGBB`, `0xFFRRGGBB`, and named color strings
2. `Paint` correctly configures style, color, alpha, stroke width, and text size
3. `Path` correctly builds and queries geometric paths with all fill types
4. `Canvas::drawRect()`, `drawCircle()`, `drawLine()`, `drawPath()`, `drawText()` record commands to internal list
5. `Canvas::save()` / `restore()` correctly manages transform state stack
6. `Canvas::clipRect()` and `clipPath()` constrain subsequent draw operations
7. `ColorDrawable::draw()` produces a draw-rect command with the correct color
8. `Drawable` bounds and intrinsic size APIs behave per Java specification
9. Unit tests verify all classes with >80% coverage
10. Integration test: View with ColorDrawable background produces correct draw commands through Canvas

## Out of Scope
- `BitmapDrawable`, `GradientDrawable`, `LayerDrawable`, `InsetDrawable`
- `Shader` class and gradient drawing
- `Bitmap` class and image loading
- Hardware rasterization / Skia integration
- Text shaping with HarfBuzz (record text draw calls; defer actual rasterization)
- `Region`, `Rasterizer`, `Picture`
- `ColorFilter`, `Xfermode`, `MaskFilter` subclasses (handle as opaque handles)
