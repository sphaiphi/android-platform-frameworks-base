# TransitionInflater - Reverse Engineering Documentation

## Executive Summary
Loads `Transition` and `TransitionManager` objects from XML resources.

## Logic
-   **Parsing**: Uses `XmlPullParser`.
-   **Registry**: `sConstructors` cache for reflection.
-   **Instantiation**: Reads class names or standard tags (`<fade>`, `<changeBounds>`) and instantiates objects.

## Java-to-C++ Translation Guide
-   **Resource System**: Requires a compatible XML parser and resource lookup mechanism.
-   **Reflection**: C++ doesn't support reflection in the same way. A factory pattern or registration map is needed for custom classes.
