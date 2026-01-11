# LauncherActivity - Reverse Engineering Documentation

## Executive Summary
`LauncherActivity` is an abstract base class that displays a list of activities that can be performed for a given intent. It is designed to act as a chooser or a launcher UI where the user can pick an application to perform a specific action. It is currently deprecated in favor of `RecyclerView` and direct usage of `PackageManager.queryIntentActivities`.

## Architecture Overview
- **Inheritance**: `LauncherActivity` extends `ListActivity`.
- **Inner Classes**:
    - `ListItem`: Represents an individual item in the list, containing `ResolveInfo`, label, icon, and component details.
    - `ActivityAdapter`: A custom `BaseAdapter` that manages the list of activities and provides filtering capabilities.
    - `IconResizer`: A utility class used to resize application icons to a standard thumbnail size.
- **Dependencies**: Heavily relies on `PackageManager` for querying intent-handling activities and loading metadata (labels, icons).

## Detailed Functionality

### onCreate(Bundle icicle)
**Purpose**: Initializes the activity, sets up the `PackageManager`, `IconResizer`, and the `ActivityAdapter`.
**Algorithm**: Sets the content view (default `activity_list`), creates a base `Intent` from `getTargetIntent()`, initializes the adapter, and sets it to the `ListView`. It also handles showing/hiding indeterminate progress for non-watch devices.

### makeListItems()
**Purpose**: Queries the system for activities that match the target intent and prepares the list of `ListItem` objects.
**Algorithm**: 
1. Calls `onQueryPackageManager(mIntent)` to get a list of `ResolveInfo`.
2. Calls `onSortResultList(list)` to sort them (default is by display name).
3. Iterates through the results and creates `ListItem` instances.

### onListItemClick(ListView l, View v, int position, long id)
**Purpose**: Handles user selection by launching the selected activity.
**Algorithm**: Retrieves the `Intent` for the clicked position via `intentForPosition(position)` and calls `startActivity(intent)`.

### IconResizer.createIconThumbnail(Drawable icon)
**Purpose**: Resizes a given drawable to fit the standard application icon size while maintaining aspect ratio.
**Algorithm**: 
1. Checks intrinsic dimensions.
2. If the icon is larger than the target size, it calculates the scaling ratio.
3. Creates a new `Bitmap` and uses a `Canvas` to draw the scaled icon centered within the thumbnail bounds.
4. Returns a `BitmapDrawable` wrapping the new bitmap.

## Data Model
### ListItem
- `ResolveInfo resolveInfo`: Metadata about the activity/service.
- `CharSequence label`: The user-visible name.
- `Drawable icon`: The standard-sized icon.
- `String packageName`: Package name of the component.
- `String className`: Class name of the component.
- `Bundle extras`: Optional extras to be added to the launch intent.

## API Reference
- `protected Intent getTargetIntent()`: Returns the base intent to query for.
- `protected List<ResolveInfo> onQueryPackageManager(Intent queryIntent)`: Performs the actual query.
- `protected void onSortResultList(List<ResolveInfo> results)`: Sorts the query results.
- `public List<ListItem> makeListItems()`: Generates the data for the adapter.

## Java-to-C++ Translation Guide
- **Activity Lifecycle**: Map to a C++ Activity framework (e.g., using `ndk_executor` or similar abstractions for lifecycle events).
- **GUI**: Use a C++ UI framework or an NDK-based UI (like `Canvas` and `Surface`) to render the list.
- **PackageManager**: Use the NDK `AAccessibilityService` or direct JNI calls to `PackageManager` via `android::content::pm::PackageManager` wrappers.
- **Adapters**: Implement a virtual list or recycler view pattern in C++.
- **Drawables/Icons**: Use `Skia` or `minikin` for bitmap manipulation and rendering if doing native UI.

## Implementation Risks
- **Deprecated status**: Since it's deprecated, the functionality might be better implemented using modern patterns rather than a direct 1:1 translation of this specific class.
- **Icon Resizing**: Native bitmap manipulation (resizing, aspect ratio math) must be carefully handled to avoid aliasing or memory leaks.
- **Threading**: `IconResizer` explicitly states it is not thread-safe and must be used on the UI thread. C++ implementation must enforce similar constraints or use proper synchronization.
