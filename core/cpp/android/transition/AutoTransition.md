# AutoTransition - Reverse Engineering Documentation

## Executive Summary
`AutoTransition` is a convenience class that defines a standard transition sequence: fading out disappearing items, moving/resizing changing items, and fading in appearing items.

## Architecture
- **Inheritance**: Extends `TransitionSet`.
- **Composition**: Contains `Fade`, `ChangeBounds`, and another `Fade`.

## Data Model
- **Ordering**: Sets ordering to `ORDERING_SEQUENTIAL`.
- **Transitions**:
    1.  `Fade(Fade.OUT)`
    2.  `ChangeBounds`
    3.  `Fade(Fade.IN)`

## API Reference
-   `AutoTransition()`: Constructs the set and initializes the sequence.
-   `AutoTransition(Context, AttributeSet)`: XML constructor.

## Java-to-C++ Translation Guide
-   **Composite Pattern**: This class primarily constructs other objects. C++ implementation should essentially be a factory or a subclass of `TransitionSet` that pushes these specific child transitions into its collection during initialization.
