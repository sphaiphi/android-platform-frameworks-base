# ContentProviderHolder - Reverse Engineering Documentation

## Executive Summary
`ContentProviderHolder` is a Parcelable class used to transfer a `IContentProvider` interface along with its metadata (`ProviderInfo`) and connection status across IPC boundaries.

## Architecture Overview
*   **Type**: Parcelable Data Container.
*   **Fields**:
    *   `info`: `ProviderInfo`.
    *   `provider`: `IContentProvider` (Binder interface).
    *   `connection`: `IBinder` (service connection token).
    *   `noReleaseNeeded`: Boolean.
    *   `mLocal`: Boolean (true if in same process).

## Java-to-C++ Translation Guide
*   Standard Parcelable.
*   Hold `sp<IContentProvider>`.

## Implementation Risks
*   **Reference Counting**: Management of the `connection` binder token is critical for releasing providers in AMS.
