# Contract: WindowManager Public API

## Interface: android::view::WindowManager

### addView

```cpp
std::expected<void, std::string> addView(
    const std::shared_ptr<View>& view,
    const std::shared_ptr<WindowLayoutParams>& params);
```

**Preconditions**:
- `view` must not be null
- `params` must not be null
- `view` must not already be registered with any WindowManager

**Postconditions**:
- A ViewRootImpl is created and registered with IWindowSession
- The view is measured, laid out, and drawn
- Returns `std::unexpected(error_message)` on failure

**Error cases**:
- `"-1": view already added to another window` (maps to BadTokenException)
- `"-2": view is not valid` (maps to IllegalArgumentException)

### updateViewLayout

```cpp
std::expected<void, std::string> updateViewLayout(
    const std::shared_ptr<View>& view,
    const std::shared_ptr<WindowLayoutParams>& params);
```

**Preconditions**:
- `view` must be registered with this WindowManager
- `params` must not be null

**Postconditions**:
- The view's layout parameters are updated
- The view is re-measured, re-laid-out, and re-drawn
- Returns `std::unexpected(error_message)` on failure

**Error cases**:
- `"-3": view is not added to this window` (maps to IllegalArgumentException)

### removeView

```cpp
std::expected<void, std::string> removeView(
    const std::shared_ptr<View>& view);
```

**Preconditions**:
- `view` must be registered with this WindowManager

**Postconditions**:
- The view is removed from the window
- The ViewRootImpl is torn down
- The view is no longer rendered
- Returns `std::unexpected(error_message)` on failure

**Error cases**:
- `"-4": view is not added to this window` (maps to IllegalArgumentException)

### getDefaultDisplay

```cpp
DisplayInfo getDefaultDisplay() const;
```

**Postconditions**:
- Returns the DisplayInfo for the display this WindowManager is bound to

## Interface: android::view::WindowManagerGlobal (Internal)

### addView (internal)

```cpp
void addView(
    std::shared_ptr<View> view,
    std::shared_ptr<WindowLayoutParams> params,
    DisplayInfo* display);
```

**Responsibilities**:
1. Validate view and params are not null
2. Check view is not already registered
3. Create ViewRootImpl, set its view, window, and window session
4. Call ViewRootImpl::set_view() to trigger IWindowSession::add_to_display()
5. Store view, params, and rootImpl in internal vectors

### updateViewLayout (internal)

```cpp
void updateViewLayout(std::shared_ptr<View> view, std::shared_ptr<WindowLayoutParams> params);
```

**Responsibilities**:
1. Find the ViewRootImpl for the given view
2. Update the LayoutParams
3. Trigger a traversal (performTraversals) on the ViewRootImpl

### removeView (internal)

```cpp
void removeView(std::shared_ptr<View> view);
```

**Responsibilities**:
1. Find the ViewRootImpl for the given view
2. Call IWindowSession::remove() to tear down the window
3. Remove view, params, and rootImpl from internal vectors
4. Destroy the ViewRootImpl

### findView (internal)

```cpp
ViewRootImpl* findView(std::shared_ptr<View> view) const;
```

**Responsibilities**:
1. Linear search through mViews to find matching view
2. Return the corresponding ViewRootImpl, or nullptr if not found
