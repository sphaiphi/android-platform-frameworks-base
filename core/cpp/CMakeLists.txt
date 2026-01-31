cmake_minimum_required(VERSION 3.22)
project(AndroidFrameworkCore CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add include directory
include_directories(include)

# Define the library
add_library(android_framework_core
    src/dummy.cpp
    src/android/os/Bundle.cpp
    src/android/os/PatternMatcher.cpp
    src/android/net/Uri.cpp
    src/android/content/Intent.cpp
    src/android/content/ComponentName.cpp
    src/android/content/ClipDescription.cpp
    src/android/content/ClipData.cpp
    src/android/content/IntentFilter.cpp
    src/android/graphics/Rect.cpp
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
)

# Link dependencies
find_library(log-lib log)
find_library(binder-ndk-lib binder_ndk)
target_link_libraries(android_framework_core ${log-lib} ${binder-ndk-lib})

enable_testing()
add_subdirectory(tests)