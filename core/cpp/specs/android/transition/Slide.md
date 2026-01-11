# Slide - Reverse Engineering Documentation

## Executive Summary
`Slide` is a `Visibility` transition. Appearing views slide in from an edge; disappearing views slide out to an edge.

## Logic
-   **Calculators**: Inner interfaces (`CalculateSlide`) determine the translation delta based on Gravity (e.g., `sCalculateBottom` modifies translationY).
-   **Animation**: Uses `TranslationAnimationCreator`.

## Java-to-C++ Translation Guide
-   **Strategies**: The strategy pattern for different edges (Left, Top, etc.) maps well to C++ classes or lambdas.
