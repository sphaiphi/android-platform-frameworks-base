include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
# For Windows: prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(framework_tests
    sanity_test.cpp
    Bundle_test.cpp
    Intent_test.cpp
)

target_link_libraries(framework_tests PRIVATE gtest_main android_framework_core)

include(GoogleTest)
gtest_discover_tests(framework_tests)
