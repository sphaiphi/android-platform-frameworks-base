# Quickstart: WindowManager

## Build

```bash
# Host build
cmake -B build -S core/cpp
cmake --build build
ctest --output-on-failure
```

## Basic Usage

### Creating a WindowManager and Adding a View

```cpp
#include <android/view/WindowManager.h>
#include <android/view/WindowManagerImpl.h>
#include <android/view/View.h>
#include <android/view/WindowLayoutParams.h>
#include <android/view/DisplayInfo.h>
#include <iostream>

int main() {
    // Create a WindowManager bound to the default display
    android::view::DisplayInfo default_display{1080, 1920, 0};
    android::view::WindowManagerImpl wm(default_display);

    // Create a view
    auto view = std::make_shared<android::view::View>();
    view->set_id(1);

    // Create layout parameters
    auto params = std::make_shared<android::view::WindowLayoutParams>(
        android::view::View::MATCH_PARENT,
        android::view::View::MATCH_PARENT
    );

    // Add the view to the window
    auto result = wm.addView(view, params);
    if (!result) {
        std::cerr << "Failed to add view: " << result.error() << std::endl;
        return 1;
    }

    std::cout << "View added successfully" << std::endl;

    // Update the view's size
    params->width = 500;
    params->height = 500;
    result = wm.updateViewLayout(view, params);
    if (!result) {
        std::cerr << "Failed to update layout: " << result.error() << std::endl;
        return 1;
    }

    // Remove the view
    result = wm.removeView(view);
    if (!result) {
        std::cerr << "Failed to remove view: " << result.error() << std::endl;
        return 1;
    }

    std::cout << "View removed successfully" << std::endl;
    return 0;
}
```

## Error Handling

```cpp
auto result = wm.addView(view, params);
if (!result) {
    // std::expected failure
    std::cerr << "Error: " << result.error() << std::endl;
    // Error messages:
    // "-1" = view already added to another window
    // "-2" = view is not valid
    // "-3" = view is not attached (updateViewLayout)
    // "-4" = view is not attached (removeView)
}
```

## Running Tests

```bash
# Run all WindowManager tests
cd build && ctest -R WindowManager --output-on-failure

# Run single test
cd build && ./tests/framework_tests --gtest_filter="WindowManagerTest.*"
```

## Verification Steps

1. **Build**: `cmake --build build` should compile without errors
2. **Unit tests**: `ctest -R WindowManager` should pass all tests
3. **Manual smoke test**: Compile and run the basic usage example above
4. **CTS validation**: Build and run CTS framework tests for WindowManager compatibility
