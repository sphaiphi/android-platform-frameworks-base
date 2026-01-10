# DataSetObserver - Reverse Engineering Documentation

## Executive Summary
`DataSetObserver` is an abstract class receiving callbacks when a data set changes or becomes invalid. It is commonly used with Cursors and Adapters.

## API Reference
*   `onChanged()`: Data has changed (requery needed or UI update).
*   `onInvalidated()`: Data is no longer valid (cursor closed).

## Java-to-C++ Translation Guide
*   **Interface**: Pure virtual class.
