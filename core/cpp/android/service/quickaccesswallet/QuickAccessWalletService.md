# QuickAccessWalletService - Reverse Engineering Documentation

## Executive Summary
`QuickAccessWalletService` is the base class for applications providing payment cards and passes to the Android Quick Access Wallet UI. This feature allows users to quickly access their default payment method and other important passes (tickets, loyalty cards) without leaving their current context.

## Architecture Overview
*   **Inheritance**: Extends `android.app.Service`.
*   **IPC**: Implements `IQuickAccessWalletService.Stub`.
*   **Permission**: Requires `android.permission.BIND_QUICK_ACCESS_WALLET_SERVICE`.
*   **Binding Requirements**: The app must also be the default NFC payment application (`HostApduService` or `OffHostApduService`).
*   **Lifecycle**: The system binds to the service when the user invokes the wallet gesture. Connections may be cached.

## Detailed Functionality

### Core Operations
*   **`onWalletCardsRequested(GetWalletCardsRequest, GetWalletCardsCallback)`**:
    *   **Goal**: Provide a list of `WalletCard` objects to be shown in the switcher.
    *   **Result**: The callback must be invoked with `onSuccess(GetWalletCardsResponse)` or `onFailure(GetWalletCardsError)`.
*   **`onWalletCardSelected(SelectWalletCardRequest)`**:
    *   **Goal**: Notify the service that a specific card is currently focused in the UI. Crucial for NFC apps to set the active payment card.
*   **`onWalletDismissed()`**:
    *   **Goal**: Notify the service that the wallet UI is no longer visible.

### Event Notifications
*   **`sendWalletServiceEvent(WalletServiceEvent)`**: Allows the service to proactively signal the system (e.g., to dismiss the wallet if an NFC transaction starts).

### UI Overrides
*   **`getTargetActivityPendingIntent()`**: (Optional) Provide a custom Activity to replace the system's card switcher.
*   **`getGestureTargetActivityPendingIntent()`**: (Optional) Custom Activity specifically for when the wallet is opened via a gesture.

## API Reference

### Constants
*   `SERVICE_INTERFACE`: `"android.service.quickaccesswallet.QuickAccessWalletService"`
*   `ACTION_VIEW_WALLET`: Action used to launch the main wallet Activity.

## Java-to-C++ Translation Guide

### IPC
*   **Java**: `IQuickAccessWalletService.Stub`.
*   **C++**: `BnQuickAccessWalletService`.

### Data Model
*   `WalletCard`, `GetWalletCardsRequest`, `GetWalletCardsResponse` are Parcelables.
*   The system uses `Icon` and `PendingIntent` heavily for card visualization and interaction.

### Threading
*   **Java**: Methods are executed on the main thread via `Handler`.
*   **C++**: Ensure thread-safe access to internal card state.

## Implementation Risks
*   **Latency**: The wallet UI should appear instantly. Requests for cards must be handled extremely fast.
*   **State Management**: While the service is stateless, the mapping between the UI's `selectedIndex` and the app's active NFC card must be consistent.
*   **Security**: Handling sensitive financial card metadata. Card IDs should not contain PII.
