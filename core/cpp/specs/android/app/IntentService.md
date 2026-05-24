# IntentService - Reverse Engineering Documentation

## Executive Summary
`IntentService` is a deprecated base class for Services that handle asynchronous requests (expressed as Intents) on a worker thread.

## Architecture Overview
*   **Inheritance**: `Service`.
*   **Pattern**: Work Queue.

## Detailed Functionality
*   **Thread**: Creates a `HandlerThread` in `onCreate`.
*   **Handling**: `onStartCommand` posts message to the handler.
*   **Processing**: `handleMessage` calls abstract `onHandleIntent(Intent)`.
*   **Stopping**: Calls `stopSelf(startId)` after handling the intent.

## Java-to-C++ Translation Guide
*   Thread/Looper/Handler implementation.

## Implementation Risks
*   **Deprecated**: Replaced by JobScheduler/WorkManager.
