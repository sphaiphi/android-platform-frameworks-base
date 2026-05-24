# DirectAction - Reverse Engineering Documentation

## Executive Summary
`DirectAction` represents an abstract action (ID + Extras) that can be performed by an app, typically requested by an external service like the Assistant or System UI. It is a data container.

## Architecture Overview
*   **Type**: Parcelable Data Class.
*   **Fields**:
    *   `mID`: String ID.
    *   `mExtras`: Bundle.
    *   `mLocusId`: LocusId (context).

## Detailed Functionality
*   **Purpose**: Used in `onGetDirectActions` and `onPerformDirectAction` in `Activity` and `VoiceInteractor`.

## Java-to-C++ Translation Guide
*   Standard Parcelable.

## Implementation Risks
*   None.
