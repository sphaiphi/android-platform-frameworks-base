# ComponentOptions - Reverse Engineering Documentation

## Executive Summary
`ComponentOptions` is the base class for `ActivityOptions` and `BroadcastOptions`. It holds common options, primarily related to `PendingIntent` background start privileges.

## Architecture Overview
*   **Type**: Base Class.
*   **Fields**: `mPendingIntentBalAllowed` (Background Activity Launch mode).

## Detailed Functionality
*   **Background Starts**: `setPendingIntentBackgroundActivityStartMode`. Controls if the PendingIntent is allowed to start activities from the background (system defined, allowed, denied).

## Java-to-C++ Translation Guide
*   Base class for Options classes.
*   Serialization to/from Bundle.

## Implementation Risks
*   None.
