# ScrollCaptureSearchResults - Reverse Engineering Documentation

## Executive Summary
`ScrollCaptureSearchResults` is a container used during the "Discovery" phase of scroll capture. It collects potential targets (Views that claim they can be captured) and implements the ranking logic to decide which one is the "best" target for the current screenshot request.

## Architecture Overview
*   **Role**: Target aggregator and ranker.
*   **Ranking Logic**:
    1.  Prioritize views with `SCROLL_CAPTURE_HINT_INCLUDE`.
    2.  Prioritize descendants over ancestors (innermost scroll container wins).
    3.  Prioritize larger scrollable areas.
    4.  (Modern) Account for Z-order and overlapping views.

## Detailed Functionality

### 1. Target Collection
*   **`addTarget()`**: Adds a `ScrollCaptureTarget` and triggers its `onScrollCaptureSearch` callback.

### 2. Ranking (`getTopResult`)
*   Implements a complex filter to remove obscured or covered targets.
*   Ensures that nested containers (like a `WebView` inside a `ScrollView`) are handled correctly based on developer hints.

## Java-to-C++ Translation Guide
*   **Collection**: Use `std::vector<ScrollCaptureTarget>`.
*   **Sorting**: Implement a custom comparator matching `PRIORITY_ORDER`.

## Implementation Risks
*   **Timeouts**: Search is asynchronous; the system must enforce a strict timeout (default 2500ms) to prevent the screenshot tool from hanging on a slow app.
*   **Z-Order Accuracy**: Incorrectly identifying which view is "on top" can lead to capturing the wrong content.
