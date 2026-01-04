# Message - Reverse Engineering Documentation

## Executive Summary
`Message` is a lightweight, recyclable data object used to define a unit of work or an event. It contains a description (what), data (arg1, arg2, obj, data), and a target `Handler`. It implements a linked-list structure for storage in the `MessageQueue` and the recycling pool.

## Architecture Overview
-   **Pattern**: Command Object / Poolable.
-   **Recycling**: Global static pool (`sPool`) avoids garbage collection churn. `obtain()` gets from pool, `recycle()` returns to pool.

## Data Model
-   **Metadata**: `what` (int), `arg1` (int), `arg2` (int), `obj` (Object).
-   **Payload**: `data` (Bundle).
-   **Routing**: `target` (Handler), `replyTo` (Messenger), `callback` (Runnable).
-   **Timing**: `when` (timestamp).
-   **Linkage**: `next` (Message) for linked list.
-   **Flags**: `FLAG_IN_USE`, `FLAG_ASYNCHRONOUS`.

## API Reference
-   `obtain()`: Factory method.
-   `sendToTarget()`: Convenience to call `target.sendMessage(this)`.
-   `copyFrom(Message)`: Shallow copy.

## Java-to-C++ Translation Guide
-   **Equivalent**: `struct Message` in `Looper.h`.
-   **Differences**: C++ Message usually just has `what` and `uptime`. It does not typically carry a `Bundle` or `Handler` reference directly in the low-level `utils` implementation, though `ALooper` allows `void*` payload.
-   **Pool**: C++ implementation might not strictly need a pool if objects are stack-allocated or small structs, but for complex payloads, a pool is beneficial.
