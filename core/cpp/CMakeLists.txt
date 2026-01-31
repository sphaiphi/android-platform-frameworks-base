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
    src/android/content/Intent.cpp
    src/android/app/Activity.cpp
    src/android/app/ContextImpl.cpp
    src/android/app/SystemServiceRegistry.cpp
    src/android/app/ActivityThread.cpp
    src/android/os/Looper.cpp
    src/android/os/Handler.cpp
    src/android/app/Instrumentation.cpp
)

# Link dependencies
find_library(log-lib log)
# target_link_libraries(android_framework_core ${log-lib})

enable_testing()
add_subdirectory(tests)