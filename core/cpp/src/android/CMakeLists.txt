# Android framework core implementation

add_library(android_framework_core ../dummy.cpp)
target_include_directories(android_framework_core PUBLIC ../include)
target_link_libraries(android_framework_core PUBLIC android_framework_headers)

# Add content subdirectory
add_subdirectory(content)
