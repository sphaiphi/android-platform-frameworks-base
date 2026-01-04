# InitArguments - Reverse Engineering Documentation

## Executive Summary
Configuration arguments for initializing the Perfetto producer.

## Data Model
*   **`backends`**: Bitmask of backends to enable (`PERFETTO_BACKEND_IN_PROCESS`, `PERFETTO_BACKEND_SYSTEM`).
*   **`shmemSizeHintKb`**: Hint for shared memory size (optional).

## API Reference
*   **`InitArguments(int backends, int shmemSizeHintKb)`**: Constructor.
*   **`DEFAULTS`**: System backend, default shmem.
*   **`TESTING`**: In-process backend.

## Java-to-C++ Translation Guide
*   **Perfetto Struct**: Maps to `perfetto::TracingInitArgs` in the C++ SDK.
