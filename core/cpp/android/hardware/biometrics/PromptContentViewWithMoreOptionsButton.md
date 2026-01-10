# PromptContentViewWithMoreOptionsButton - Reverse Engineering Documentation

## Executive Summary
`PromptContentViewWithMoreOptionsButton` defines a content view template that includes a description and a "more options" button. This is used when the app needs to offer complex choices (like picking an account) within the auth flow.

## Detailed Functionality
- **Data**: `mDescription` (String).
- **Callback**: `mListener` (OnClickListener) and `mExecutor`.
- **Parceling**: Only the description is parceled. The listener is NOT parceled (it's process-local).
- **ButtonInfo**: Internal helper class to store the listener/executor.

## Java-to-C++ Translation Guide
- **Data**: `struct { std::string description; }`.
- **Callback**: The callback is local to the app process. The system service only knows about the description. When the UI (SystemUI) is dismissed with "More Options", a specific dismissal reason (`DISMISSED_REASON_CONTENT_VIEW_MORE_OPTIONS`) is sent back to the app, which triggers the local listener.

## Implementation Risks
- Ensuring the listener logic is handled correctly when the prompt is dismissed via IPC.
