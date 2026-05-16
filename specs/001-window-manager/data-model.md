# Data Model: WindowManager

## Entities

### WindowManager (Public Interface)

The public API that NDK developers use to manage windows.

| Field | Type | Description |
|-------|------|-------------|
| (none) | — | Stateless facade; all state lives in WindowManagerGlobal |

**Methods**:
- `addView(View*, WindowLayoutParams*) -> std::expected<void, std::string>`
- `updateViewLayout(View*, WindowLayoutParams*) -> std::expected<void, std::string>`
- `removeView(View*) -> std::expected<void, std::string>`
- `getDefaultDisplay() -> DisplayInfo`

### WindowManagerGlobal (Internal Singleton)

Manages the lifecycle of all views registered with any WindowManager instance.

| Field | Type | Description |
|-------|------|-------------|
| mRoots | `std::vector<std::unique_ptr<ViewRootImpl>>` | Root views (one per window) |
| mViews | `std::vector<std::shared_ptr<View>>` | Root view references |
| mRootLayoutParams | `std::vector<std::shared_ptr<WindowLayoutParams>>` | Layout parameters per window |
| mDisplays | `std::vector<DisplayInfo>` | Available displays |

**Methods**:
- `addView(View*, WindowLayoutParams*, DisplayInfo*) -> void`
- `updateViewLayout(View*, WindowLayoutParams*) -> void`
- `removeView(View*) -> void`
- `findView(View*) -> ViewRootImpl*` (internal lookup)
- `getDefaultDisplay() -> DisplayInfo`
- `getDisplays() -> const std::vector<DisplayInfo>&`

### WindowManagerImpl (Delegator)

Thin wrapper that delegates all operations to WindowManagerGlobal. Constructed per-display.

| Field | Type | Description |
|-------|------|-------------|
| mGlobal | `WindowManagerGlobal&` | Reference to singleton |
| mDisplay | `DisplayInfo` | Bound display info |

**Methods**: Delegates all operations to `mGlobal`.

### WindowLayoutParams

Window-specific layout parameters extending base LayoutParams.

| Field | Type | Description |
|-------|------|-------------|
| width | int32_t | View width (MATCH_PARENT, WRAP_CONTENT, or pixel value) |
| height | int32_t | View height |
| type | int32_t | Window type (APPLICATION = 1, SYSTEM_OVERLAY = -2, etc.) |
| flags | int32_t | Window flags (NOT_FOCUSABLE, NOT_TOUCHABLE, etc.) |
| format | int32_t | Pixel format (TRANSLUCENT, TRANSPARENT, OPAQUE) |
| gravity | int32_t | Gravity (from Gravity enum) |
| x | int32_t | X offset |
| y | int32_t | Y offset |
| alpha | float32_t | Window alpha (0.0 - 1.0) |
| softInputMode | int32_t | Soft input mode |

### View Registration Entry (Internal)

Each view registered with WindowManagerGlobal is tracked as a tuple:

| Field | Type | Description |
|-------|------|-------------|
| view | `std::shared_ptr<View>` | The root view |
| params | `std::shared_ptr<WindowLayoutParams>` | Its layout parameters |
| rootImpl | `std::unique_ptr<ViewRootImpl>` | Its ViewRootImpl |
| display | `DisplayInfo` | The display it's bound to |

## Relationships

```
WindowManagerImpl ──delegates──> WindowManagerGlobal
WindowManagerGlobal ──contains──> vector<View, WindowLayoutParams*, ViewRootImpl>
WindowManagerGlobal ──contains──> vector<DisplayInfo>
ViewRootImpl ──implements──> IWindow
ViewRootImpl ──uses──> IWindowSession (via WindowSession)
```

## State Transitions

### View Lifecycle

```
[unregistered] --> addView() --> [registered] --> updateViewLayout() --> [registered]
[registered] --> removeView() --> [unregistered]
[registered] --> (display disconnect) --> [removed, InvalidDisplayException]
```

### Validation Rules

1. A view can only be in `[registered]` state once (no duplicates)
2. `updateViewLayout()` requires `[registered]` state
3. `removeView()` requires `[registered]` state
4. After `removeView()`, the view returns to `[unregistered]` and can be re-added
