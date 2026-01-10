# TextView - Reverse Engineering Documentation

## Executive Summary
`TextView` is one of the most complex and fundamental views in Android. It displays text, handles rich text styling (Spans), manages text layout (Static/Dynamic), handles input (EditText functionality via Editor), and supports scrolling, selection, and accessibility.

## Architecture Overview
*   **Inheritance**: `View` -> `TextView`.
*   **Subclasses**: `EditText`, `Button`, `CheckedTextView`, etc.
*   **Delegates**:
    *   `Editor`: Handles all editing, cursor, selection, and IME logic (lazy-loaded).
    *   `Layout` (`StaticLayout`, `DynamicLayout`, `BoringLayout`): Handles text measurement, line breaking, and drawing.
    *   `TransformationMethod`: Modifies text before display (e.g., Password, AllCaps).
    *   `MovementMethod`: Handles cursor movement and scrolling via keys/touch.

## Detailed Functionality

### 1. Text Storage (`BufferType`)
*   **NORMAL**: Stored as `String` (immutable).
*   **SPANNABLE**: Stored as `SpannableString` (immutable text, mutable markup).
*   **EDITABLE**: Stored as `SpannableStringBuilder` (mutable text and markup).

### 2. Layout & Measurement (`onMeasure`)
*   **BoringLayout**: Optimization for single-line, left-to-right text with no special characters.
*   **StaticLayout**: For multi-line, non-editable text.
*   **DynamicLayout**: For editable text (updates partially on change).
*   **Logic**: Calculates desired width/height based on text content, `maxLines`, `ellipsize`, padding, and compounds drawables.

### 3. Drawing (`onDraw`)
*   **Background**: Drawn by View.
*   **Compound Drawables**: Draws icons (left/top/right/bottom).
*   **Layout**: `mLayout.draw()` renders the text.
*   **Editor**: If editable, `mEditor.onDraw()` renders the cursor, selection highlight, and handles.
*   **Marquee**: Handles horizontal scrolling animation if enabled.

### 4. Input & Interaction
*   **Key Events**: Delegates to `MovementMethod` (arrows) or `Editor` (typing).
*   **Touch**: Handles scrolling and caret positioning. `Editor` handles long-press for selection/paste menu.
*   **IME**: Creates `InputConnection` to communicate with the soft keyboard.

### 5. Styling (TextAppearance)
*   Parses attributes (textSize, textColor, typeface, shadow, etc.).
*   Applies them to `mTextPaint`.

## Java-to-C++ Translation Guide
*   **Complexity Warning**: This class is massive. It should be split into smaller components in a C++ engine (e.g., `TextRenderer`, `TextEditor`, `TextLayout`).
*   **Text Layout Engine**: Requires a robust text shaping and layout engine (like Skia's SkParagraph or HarfBuzz/Minikin).
*   **Spans**: The `Spannable` interface and its integration with the layout engine is the core difficulty.

## Implementation Risks
*   **Performance**: Text measurement is slow. Android uses `BoringLayout` and `PrecomputedText` to optimize.
*   **Internationalization**: BiDi (Bidirectional text), complex scripts, line breaking rules (ICU).
*   **IME**: Proper integration with the OS input method is critical and platform-specific.