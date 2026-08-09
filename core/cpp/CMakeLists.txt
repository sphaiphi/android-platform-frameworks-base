cmake_minimum_required(VERSION 3.20)
project(port_package_info LANGUAGES CXX)

# Use C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Add Android framework native headers
set(FW_NATIVE_INCLUDE "$ENV{ANDROID_FRAMEWORK_NATIVE_HOME}/include" CACHE PATH "Path to android_frameworks_native/include")
if(NOT EXISTS "${FW_NATIVE_INCLUDE}")
    # Try common locations
    if(EXISTS "/home/roto/git/android_frameworks_native/include")
        set(FW_NATIVE_INCLUDE "/home/roto/git/android_frameworks_native/include")
    elseif(EXISTS "$ENV{HOME}/git/android_frameworks_native/include")
        set(FW_NATIVE_INCLUDE "$ENV{HOME}/git/android_frameworks_native/include")
    endif()
endif()
if(EXISTS "${FW_NATIVE_INCLUDE}")
    message(STATUS "Using android_frameworks_native headers from: ${FW_NATIVE_INCLUDE}")
    include_directories("${FW_NATIVE_INCLUDE}")
else()
    message(WARNING "android_frameworks_native headers not found. Build may fail.")
endif()

# Add subdirectories
add_subdirectory(include/android)
add_subdirectory(src/android)
add_subdirectory(tests)

# Host-side tool for package-info header generation
add_subdirectory(tools/package_info_generator)
