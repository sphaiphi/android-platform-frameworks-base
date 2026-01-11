# TranslationAnimationCreator - Reverse Engineering Documentation

## Executive Summary
Helper used by `Slide` and `Explode` to create translation animations.

## Key Logic
-   **Interruption Handling**: Checks `R.id.transitionPosition` tag. If a view is already animating (interrupted), it calculates the start position relative to the current position to avoid jumps.
-   **Animation**: `ObjectAnimator` for TranslationX/Y.
-   **Listener**: `TransitionPositionListener` pauses/resumes the view's translation properties.

## Java-to-C++ Translation Guide
-   **State Persistence**: Uses View tags to store interruption state. C++ needs a similar mechanism (component data or property bag) on UI nodes.
