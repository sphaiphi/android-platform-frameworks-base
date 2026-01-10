# SpellCheckerSession - Reverse Engineering Documentation

## Executive Summary
Represents a client's connection to a Spell Checker Service. It manages the lifecycle of the session and provides methods to request suggestions.

## Architecture
*   **Listeners**: `SpellCheckerSessionListener` (client callback), `InternalListener` (Binder callback).
*   **Threading**: Uses `HandlerThread` ("SpellCheckerSession") to handle async tasks from the service.
*   **Manager**: Communicates via `TextServicesManager`.

## Key Algorithms
*   **`getSuggestions`**: Queues a task. If connected, calls service immediately. If not, queues until connected.
*   **Queueing**: `mPendingTasks` queue handles requests made before the service is bound.

## Java-to-C++ Translation Guide
*   **Callbacks**: C++ callback interface.
*   **Task Queue**: `std::queue` with mutex.
