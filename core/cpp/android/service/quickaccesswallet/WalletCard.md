# WalletCard - Reverse Engineering Documentation

## Executive Summary
`WalletCard` is a data class (Parcelable) representing a single item in the Quick Access Wallet. This can be a payment card, a transit pass, a ticket, or a loyalty card. It includes visual metadata and an interaction intent.

## Data Model

### Fields
*   **`mCardId`**: `String` (NonNull) - Unique identifier for the card. Must not contain PII.
*   **`mCardType`**: `int` - `CARD_TYPE_PAYMENT`, `NON_PAYMENT`, or `UNKNOWN`.
*   **`mCardImage`**: `Icon` (NonNull) - The main visual representation (the "card art"). Should be `Config.HARDWARE` bitmap.
*   **`mContentDescription`**: `CharSequence` (NonNull) - Accessibility text.
*   **`mPendingIntent`**: `PendingIntent` (NonNull) - Action triggered when the card is clicked. Usually opens the card's details in the wallet app.
*   **`mCardIcon`**: `Icon` (Optional) - Small icon shown next to the label (e.g., NFC logo).
*   **`mCardLabel`**: `CharSequence` (Optional) - Text label (e.g., "Hold near reader").
*   **`mNonPaymentCardSecondaryImage`**: `Icon` (Optional) - Image shown when a non-payment card is tapped (e.g., a barcode).
*   **`mCardLocations`**: `List<Location>` - Geofencing info for location-based suggestions.

## API Reference

### Constants (Card Types)
*   `CARD_TYPE_UNKNOWN`: 0
*   `CARD_TYPE_PAYMENT`: 1
*   `CARD_TYPE_NON_PAYMENT`: 2

### Builder (`WalletCard.Builder`)
*   **Constructor**: Requires `cardId`, `cardImage`, `contentDescription`, and `pendingIntent`.
*   **Setters**: `setCardType`, `setCardIcon`, `setCardLabel`, `setNonPaymentCardSecondaryImage`, `setCardLocations`.

## Java-to-C++ Translation Guide

### Parcelable
*   **Java**: Custom serialization for `Icon` and `PendingIntent` (using `writePendingIntentOrNullToParcel`).
*   **C++**: `android::Parcelable`.
    *   Must match the `writeByte(0/1)` logic used for optional icons.
    *   `Location` is also a Parcelable that needs a C++ equivalent.

### Performance
*   `mCardImage` should ideally be a Hardware Bitmap to minimize memory transfer and rendering overhead in the System UI process.

## Implementation Notes
*   **Immutable**: The object is immutable after construction via the builder.
*   **Privacy**: `cardId` and `cardLabel` are sensitive; implementation should avoid logging full values.
