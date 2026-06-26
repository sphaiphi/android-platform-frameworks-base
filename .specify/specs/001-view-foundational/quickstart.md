# Quickstart: Foundational View Classes

**Feature ID:** 001-view-foundational

---

## Prerequisites

### Tools

- **CMake** 3.22+ (for host builds)
- **C++23 compiler**: Clang 17+ (NDK r27+) or GCC 13+
- **GoogleTest**: Automatically fetched via FetchContent (v1.15.2)
- **bash** 4.0+

### Repository Structure

```
android-platform-frameworks-base/
  core/cpp/
    CMakeLists.txt              -- Main library build
    include/android/view/       -- Public headers
    src/android/view/           -- Implementation sources
    tests/
      CMakeLists.txt            -- Test build
      View_foundational_test.cpp
      ViewGroup_foundational_test.cpp
      ViewParentMixin_test.cpp
      ViewManagerMixin_test.cpp
```

---

## Step-by-Step Setup

### 1. Clone and Navigate

```bash
cd /home/roto/git/android-platform-frameworks-base
git checkout lineageos-23.0
```

### 2. Configure Host Build

```bash
mkdir -p build
cd build
cmake \
  -DCMAKE_CXX_STANDARD=23 \
  -DCMAKE_CXX_COMPILER=clang++ \
  -DCMAKE_BUILD_TYPE=Debug \
  -DANDROID_NDK_HOME=$ANDROID_NDK_HOME \
  ..
```

### 3. Build

```bash
cmake --build . --config Debug -j$(nproc)
```

This builds:
- `libandroid_framework_core.so` (or `.a` static) -- the main library
- `framework_tests` -- the test executable

### 4. Run Tests

```bash
./framework_tests
```

Or run specific test suites:

```bash
./framework_tests --gtest_filter="View*"
./framework_tests --gtest_filter="ViewGroup*"
./framework_tests --gtest_filter="ViewParentMixin*"
./framework_tests --gtest_filter="ViewManagerMixin*"
./framework_tests --gtest_filter="LayoutParams*"
```

### 5. Verify Coverage

```bash
# With gcov/lcov (GCC) or llvm-cov (Clang)
llvm-cov show framework_tests \
  -instr-profile=default.profdata \
  -object=framework_tests \
  --ignore-filename-regex='googletest' \
  --show-line-counts-or-regions
```

Target: >80% coverage per module.

---

## Verifying the Feature End-to-End

A minimal smoke test that validates the core feature:

```cpp
#include <android/view/View.h>
#include <android/view/ViewGroup.h>
#include <android/view/LayoutParams.h>
#include <cassert>

int main() {
    using namespace android::view;

    // 1. Create a ViewGroup
    ViewGroup<> root;
    root.layout(0, 0, 800, 600);

    // 2. Create a child View
    View child;
    child.layout(10, 20, 110, 70);
    assert(child.get_left() == 10);
    assert(child.get_top() == 20);
    assert(child.get_width() == 100);
    assert(child.get_height() == 50);

    // 3. Add child to ViewGroup
    auto params = std::make_shared<MarginLayoutParams>(
        MarginLayoutParams::WRAP_CONTENT,
        MarginLayoutParams::WRAP_CONTENT
    );
    root.add_view(std::make_shared<View>(/* context */ nullptr, params);
    assert(root.get_child_count() == 1);

    // 4. Verify parent reference
    assert(root.get_child_at(0)->get_parent() == &root);

    // 5. Verify properties
    assert(root.get_child_at(0)->get_alpha() == 1.0f);
    assert(root.get_child_at(0)->get_visibility() == Visibility::Visible);

    // 6. Remove child
    root.remove_view(root.get_child_at(0));
    assert(root.get_child_count() == 0);

    return 0;
}
```

---

## Common Gotchas

### 1. CRTP requires correct derived type

When defining a class that inherits from `ViewParentMixin<Self>`, the template argument MUST be the exact derived class type (not a base class). Incorrect:

```cpp
// WRONG: Base is not the actual class
class MyViewGroup : public View, public ViewParentMixin<ViewGroup> { ... };

// CORRECT: Template argument matches the exact class name
class MyViewGroup : public View, public ViewParentMixin<MyViewGroup> { ... };
```

### 2. ViewGroup template parameter

ViewGroup is now templated: `ViewGroup<TLayoutParams>`. The default is `MarginLayoutParams`. When creating a custom ViewGroup subclass, pass the correct LayoutParams type:

```cpp
class MyFrameLayout : public ViewGroup<MyFrameLayoutParams> { ... };
```

### 3. Visibility enum values

Visibility uses `enum class Visibility : int` with values matching Java (Visible=0, Invisible=4, Gone=8). Do NOT use boolean visibility -- the enum is required for ABI compatibility.

### 4. Single-threaded model

All View operations must occur on the same thread (the UI thread). In debug builds, cross-thread calls trigger assertions. In release builds, they are silently ignored. Do not add mutex protection -- it would violate the zero-cost abstraction principle.

### 5. LayoutParams vs MarginLayoutParams

LayoutParams is the base class. MarginLayoutParams adds margin fields. ViewGroup<T> uses T (defaulting to MarginLayoutParams) for child LayoutParams. When calling addView(), pass the correct type:

```cpp
// Correct: uses the ViewGroup's TLayoutParams type
root.add_view(child, std::make_shared<MarginLayoutParams>(
    MarginLayoutParams::MATCH_PARENT,
    MarginLayoutParams::MATCH_PARENT
));
```

### 6. Canvas interface

The draw() methods require `android::graphics::Canvas` with the 6 methods from FR-14a. If the existing Canvas lacks any of these (drawColor, drawRect, save, restore, clipRect, translate), add them before implementing View::draw().

### 7. Context parameter

The View constructor requires a Context argument. If the existing Context type is not yet available, use a minimal mock Context for testing. The real Context integration happens when the Context module is complete.
