# ReceiverCallNotAllowedException - Reverse Engineering Documentation

## Executive Summary
`ReceiverCallNotAllowedException` is a runtime exception thrown when a `BroadcastReceiver` attempts to call asynchronous methods (like `registerReceiver` or `bindService`) from within `onReceive`.

## Architecture Overview
- **Inheritance:** Extends `AndroidRuntimeException`.

## Java-to-C++ Translation Guide
- **Exception**: Standard exception.

## Implementation Risks
- None.