# ParcelableUsageEventList - Reverse Engineering Documentation

## Executive Summary
`ParcelableUsageEventList` is a specialized IPC transport class. Its purpose is to transfer a large list of `UsageEvents.Event` objects across Binder. Because Binder has a transaction size limit (typically 1MB), sending a large history of events can fail. This class implements a mechanism to split the list into chunks and transfer them via a side-channel Binder transaction if necessary.

## Architecture Overview
- **Implements**: `Parcelable`.
- **Core Problem**: `TransactionTooLargeException`.
- **Solution**: "Inline" vs "Binder-based" transfer.
    - Small lists are written directly ("inline").
    - Large lists write as many as fit, then pass a `Binder` object. The receiver calls this Binder to fetch the rest of the items in subsequent transactions.

## Detailed Functionality

### Writing to Parcel (`writeToParcel`)
1.  Write total count `N`.
2.  Iterate through the list.
3.  **Check Size**: Check `dest.dataSize()`.
4.  **Inline Writing**: If size < `MAX_IPC_SIZE` (suggested limit), write the event (marker `1` then event data).
5.  **Stop Inline**: If size limit reached, stop inline writing.
6.  **Binder Handoff**:
    - Write marker `0` to signal end of inline data.
    - Create a anonymous `Binder` (server-side of the data transfer).
    - **OnTransact** (in the Binder):
        - Receives request for more data (offset `i`).
        - Writes events starting from `i` into the reply parcel until limit is reached again.
        - If more data remains, returns status to continue; else signals completion.
    - Write this Binder to the main `dest` Parcel.

### Reading from Parcel (Constructor)
1.  Read total count `N`.
2.  **Read Inline**: Loop reading events while marker is `1`. Add to list.
3.  **Binder Pickup**:
    - If `i < N` (list incomplete), read the `IBinder` retriever.
    - **Loop**:
        - Create `data` Parcel with offset `i`.
        - `transact` with the retriever.
        - Read events from `reply` Parcel.
        - Repeat until all `N` items are read.

## Data Model
- `mList`: `List<UsageEvents.Event>`.

## API Reference
- `getList()`: Returns the re-assembled list.

## Java-to-C++ Translation Guide
- **Complex Logic**: This requires implementing a native Binder object (`BbBinder` in C++) to handle the data fetching callback.
- **Protocol**:
    - **Transaction Code**: `IBinder::FIRST_CALL_TRANSACTION`.
    - **Input**: Int (offset).
    - **Output**: Series of events (Int marker 1 + Event, ... Int marker 0).
- **Parcel Limits**: Use `IBinder::getSuggestedMaxIpcSizeBytes()` equivalent in C++.

## Implementation Risks
- **Concurrency**: The anonymous Binder must keep the source list alive while the transaction is happening. In Java, this is handled by the anonymous inner class capturing the list. In C++, lifetime management of the source data is crucial (e.g., `sp<ParsedListProvider>`).
- **Deadlocks**: Ensure the data fetching loop doesn't block the main Binder thread in a way that causes starvation, though usually safe as it's a synchronous call to a transient object.
