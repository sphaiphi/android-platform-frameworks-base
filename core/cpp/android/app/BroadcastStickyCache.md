# BroadcastStickyCache - Reverse Engineering Documentation

## Executive Summary
`BroadcastStickyCache` is a client-side cache for sticky broadcasts. It intercepts calls to `registerReceiver` for known sticky actions (e.g., `BATTERY_CHANGED`) and returns the cached Intent if available, avoiding IPC to `ActivityManagerService`.

## Architecture Overview
*   **Static Cache**: Uses `IpcDataCache` (property invalidated cache mechanism).
*   **Key**: `StickyBroadcastFilter` (action + filter match).

## Detailed Functionality
*   **Actions**: Caches specific list: Battery, Charging, Connectivity, HDMI, Wifi state, etc.
*   **Mechanism**: `getIntent` checks cache. If miss, calls `ActivityManager.registerReceiverWithFeature` and populates cache.
*   **Invalidation**: Relies on system property invalidation or manual invalidation when new broadcasts are received (though sticky broadcasts are usually updated by the system).

## Java-to-C++ Translation Guide
*   **Caching**: Implement a similar caching layer if performance of `registerReceiver` is critical for sticky intents.
*   **Filter Matching**: Requires `IntentFilter` matching logic.

## Implementation Risks
*   **Staleness**: Cache must be invalidated when the sticky value changes. The implementation relies on `IpcDataCache` which usually ties to a system property generation tracker.
