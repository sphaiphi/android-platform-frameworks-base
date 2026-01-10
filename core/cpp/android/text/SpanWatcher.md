# SpanWatcher - Reverse Engineering Documentation

## Executive Summary
Interface for objects that want to be notified when spans are added, removed, or changed in a `Spannable`. Extends `NoCopySpan`.

## API Reference
- **`onSpanAdded`**
- **`onSpanRemoved`**
- **`onSpanChanged`**

## Java-to-C++ Translation Guide
- **Observer Pattern**: The `Spannable` implementation needs to maintain a list of watchers and notify them.
