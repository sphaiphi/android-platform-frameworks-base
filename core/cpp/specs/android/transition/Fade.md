# Fade - Reverse Engineering Documentation

## Executive Summary
`Fade` is a standard `Visibility` transition that animates the alpha channel.

## Logic
-   **Modes**: `IN` (Appear), `OUT` (Disappear).
-   **`onAppear`**: Animates `transitionAlpha` from 0 to 1.
-   **`onDisappear`**: Animates `transitionAlpha` from 1 to 0.
-   **Listener**: Resets alpha to 1 at the end.

## Java-to-C++ Translation Guide
-   **Layer Types**: Java uses `setLayerType` to optimize alpha rendering (hardware layers). C++ implementation might handle this via render pass batching or compositor layers.
-   **Properties**: Maps to opacity/alpha.
