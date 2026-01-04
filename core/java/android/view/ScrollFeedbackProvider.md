# ScrollFeedbackProvider - Reverse Engineering Documentation

## Executive Summary
`ScrollFeedbackProvider` is a high-level interface for providing consistent user feedback (primarily haptic) during scrolling interactions. it allows components like list views or sliders to report their movement, limits, and snapping events to a centralized engine that manages the physical device responses.

## Architecture Overview
*   **Role**: Abstract scroll feedback engine.
*   **Default Implementation**: `HapticScrollFeedbackProvider`.
*   **Source Independence**: Designed to handle input from various sources (Touchscreen, Mouse, Rotary Encoder).

## Detailed Functionality

### 1. Progress Reporting
*   **`onScrollProgress()`**: Called as the user scrolls. Maps pixel distance to haptic "ticks."

### 2. Event Notifications
*   **`onScrollLimit()`**: Triggers when the user hits the top or bottom of a container.
*   **`onSnapToItem()`**: Triggers when a scroll settles on a specific discrete item.

## Java-to-C++ Translation Guide
*   **Interface**: Define as a pure virtual class in C++.
*   **Factory**: `createProvider()` is a static factory method that should return the system's preferred native implementation.

## Implementation Risks
*   **Feedback Storm**: High-frequency scrolling could lead to excessive haptic events. Implementations should include rate-limiting or debouncing.
