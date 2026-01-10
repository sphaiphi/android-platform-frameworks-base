# ParcelableMap - Reverse Engineering Documentation

## Executive Summary
A `HashMap<AutofillId, AutofillValue>` that implements `Parcelable`. Used to pass autofill datasets across IPC.

## Java-to-C++ Translation Guide
*   **Serialization**: Custom parceling for a map.
