# PendingHostUpdate - Reverse Engineering Documentation

## Executive Summary
`PendingHostUpdate` is a `Parcelable` data transfer object (DTO) used to send deferred updates from the `AppWidgetService` to the `AppWidgetHost`. When a host starts listening, it may receive a batch of these updates to sync its state.

## Data Model

### Update Types (`type` field)
1. `TYPE_VIEWS_UPDATE`: New `RemoteViews` content.
2. `TYPE_PROVIDER_CHANGED`: The provider info (`AppWidgetProviderInfo`) has changed.
3. `TYPE_VIEW_DATA_CHANGED`: Collection view data needs refresh.
4. `TYPE_APP_WIDGET_REMOVED`: Widget instance removed.

### Payload Fields
- `int appWidgetId`: Target widget.
- `RemoteViews views`: For view updates.
- `AppWidgetProviderInfo widgetInfo`: For provider info updates.
- `int viewId`: Target view ID (for data changes).

## Java-to-C++ Translation Guide
- **Tagged Union**: This acts like a tagged union or `std::variant`.
- **Serialization**: Standard Parcelable. The write logic uses `writeNullParcelable` to handle optional fields based on the type.

```cpp
struct PendingHostUpdate {
    int appWidgetId;
    int type; // Enum
    // Union or std::optional fields
    std::optional<RemoteViews> views;
    std::optional<AppWidgetProviderInfo> widgetInfo;
    int viewId;
};
```
