cmake_minimum_required(VERSION 3.22)
project(AndroidFrameworkCtsTests CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include the core framework includes
include_directories(../../../core/cpp/include)

# GoogleTest setup
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Define the CTS test executable
add_executable(framework_cts_tests
    Bundle_cts_test.cpp
    Intent_cts_test.cpp
    Activity_cts_test.cpp
    ../../../core/cpp/src/android/os/Bundle.cpp
    ../../../core/cpp/src/android/content/Intent.cpp
    ../../../core/cpp/src/android/app/Activity.cpp
    ../../../core/cpp/src/android/app/ContextImpl.cpp
    ../../../core/cpp/src/android/app/SystemServiceRegistry.cpp
    ../../../core/cpp/src/android/app/ActivityThread.cpp
    ../../../core/cpp/src/android/app/Instrumentation.cpp
    ../../../core/cpp/src/android/os/Looper.cpp
    ../../../core/cpp/src/android/os/Handler.cpp
)

target_link_libraries(framework_cts_tests PRIVATE gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(framework_cts_tests)