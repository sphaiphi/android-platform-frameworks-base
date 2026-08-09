# Android framework content implementation

add_library(android_content_core
    ClipData.cpp
    ClipDescription.cpp
    ComponentName.cpp
    Intent.cpp
    IntentFilter.cpp
)
target_include_directories(android_content_core PUBLIC ../../../../include)
target_link_libraries(android_content_core PUBLIC android_framework_headers)

# Add res subdirectory
add_subdirectory(res)

# Add pm subdirectory
add_subdirectory(pm)
