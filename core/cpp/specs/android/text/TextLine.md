# TextLine - Reverse Engineering Documentation

## Executive Summary
Represents a single line of styled text. Handles measuring, shaping, and drawing of visual runs. This is a transient object (pooled) used by `Layout`.

## Core Responsibilities
- **Breaking into Runs**: Identifies Bidi runs and Style runs (`MetricAffectingSpan`, `ReplacementSpan`).
- **Measuring**: Calculates signed width of runs.
- **Drawing**: Draws text runs, background spans, underlines, etc.

## Key Algorithms
- **`handleRun`**: The workhorse. Iterates through spans within a Bidi run.
- **`measure`**: Computes width.
- **`draw`**: Calls `Canvas.drawTextRun`.

## Java-to-C++ Translation Guide
- **Optimization**: `TextLine` in Java avoids object allocation by reusing instances. In C++, stack allocation or similar pooling is useful.
- **Shaping**: Interfaces with text shaping engine (HarfBuzz via Minikin).
- **Decorations**: Handles underlines, strikethrough logic (merging overlapping styles).
