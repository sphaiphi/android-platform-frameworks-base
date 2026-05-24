cmake_minimum_required(VERSION 3.22)
project(AndroidFrameworkCore CXX)

# Prefer clang over GCC for better C++23 support
if(NOT CMAKE_CXX_COMPILER)
  find_program(CLANGXX clang++)
  if(CLANGXX)
    set(CMAKE_CXX_COMPILER "${CLANGXX}" CACHE STRING "C++ compiler (clang preferred)")
  endif()
endif()
if(NOT CMAKE_C_COMPILER)
  find_program(CLANG clang)
  if(CLANG)
    set(CMAKE_C_COMPILER "${CLANG}" CACHE STRING "C compiler (clang preferred)")
  endif()
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add include directory
include_directories(include)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND NOT ANDROID)
    include_directories(include/android_mock)
    add_definitions(-DHOST_BUILD)
endif()

set(CORE_SOURCES
    src/dummy.cpp
    src/android/os/Bundle.cpp
    src/android/os/PatternMatcher.cpp
    src/android/net/Uri.cpp
    src/android/content/Intent.cpp
    src/android/content/ComponentName.cpp
    src/android/content/res/AssetManager.cpp
    src/android/content/res/Configuration.cpp
    src/android/content/res/Resources.cpp
    src/android/content/ClipDescription.cpp
    src/android/content/ClipData.cpp
    src/android/content/IntentFilter.cpp
    src/android/graphics/Rect.cpp
    src/android/graphics/Color.cpp
    src/android/graphics/Paint.cpp
    src/android/graphics/Path.cpp
    src/android/graphics/Canvas.cpp
    src/android/graphics/Drawable.cpp
    src/android/graphics/ColorDrawable.cpp
    src/android/app/Activity.cpp
    src/android/app/ActivityClient.cpp
    src/android/app/ActivityManager.cpp
    src/android/app/ActivityTaskManager.cpp
    src/android/app/ActivityOptions.cpp
    src/android/app/ActivityTransitionState.cpp
    src/android/app/ActivityTransitionCoordinator.cpp
    src/android/app/ContextImpl.cpp
    src/android/app/SystemServiceRegistry.cpp
    src/android/app/ActivityThread.cpp
    src/android/os/Looper.cpp
    src/android/os/Handler.cpp
    src/android/app/Instrumentation.cpp
    src/android/app/ServiceStartNotAllowedException.cpp
    src/android/app/Application.cpp
    src/android/app/ActivityGroup.cpp
    src/android/app/AliasActivity.cpp
    src/android/app/AppOpsManager.cpp
    src/android/app/Notification.cpp
    src/android/app/NativeActivity.cpp
    src/android/view/ViewConfiguration.cpp
    src/android/view/View.cpp
    src/android/view/ViewGroup.cpp
    src/android/view/Window.cpp
    src/android/view/ViewRootImpl.cpp
    src/android/view/Surface.cpp
    src/android/view/InputChannel.cpp
    src/android/view/InputEvent.cpp
    src/android/view/InputEventReceiver.cpp
    src/android/view/MotionEvent.cpp
    src/android/view/KeyEvent.cpp
    src/android/view/InsetsSourceControl.cpp
    src/android/view/InsetsSourceControlArray.cpp
    src/android/view/WindowSession.cpp
    src/android/view/WindowLayoutParams.cpp
    src/android/view/WindowManager.cpp
    src/android/view/WindowManagerGlobal.cpp
    src/android/view/WindowManagerImpl.cpp
    src/android/graphics/Point.cpp
    src/android/graphics/Insets.cpp
    src/android/widget/LinearLayout.cpp
    src/android/widget/FrameLayout.cpp
    src/android/widget/RelativeLayout.cpp
    src/android/widget/TextView.cpp
    src/android/widget/Button.cpp
    src/android/util/DisplayMetrics.cpp
    src/android/util/TypedValue.cpp
)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND NOT ANDROID)
    list(APPEND CORE_SOURCES src/android_mock/binder_mock.cpp)
endif()

# Define the library
add_library(android_framework_core ${CORE_SOURCES})

# Link dependencies
find_library(log-lib log)
find_library(binder-ndk-lib binder_ndk)

if(log-lib)
    target_link_libraries(android_framework_core ${log-lib})
endif()

if(binder-ndk-lib)
    target_link_libraries(android_framework_core ${binder-ndk-lib})
endif()

enable_testing()
add_subdirectory(tests)