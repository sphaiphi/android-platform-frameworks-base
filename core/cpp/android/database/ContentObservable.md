# ContentObservable - Reverse Engineering Documentation

## Executive Summary
`ContentObservable` is a specialized `Observable` for `ContentObserver`. It handles dispatching content change notifications to registered observers.

## Architecture Overview
*   **Inheritance**: `Observable<ContentObserver>`.

## Detailed Functionality
*   `dispatchChange(boolean selfChange, Uri uri)`:
    *   Iterates registered `ContentObserver`s.
    *   Checks `observer.deliverSelfNotifications()` if `selfChange` is true.
    *   Calls `observer.dispatchChange`.

## Java-to-C++ Translation Guide
*   **Inheritance**: `class ContentObservable : public Observable<ContentObserver>`.
