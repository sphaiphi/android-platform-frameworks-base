# Android framework content/pm implementation

add_library(android_content_pm_core
    package_info.cpp
)
target_include_directories(android_content_pm_core PUBLIC ../../../../include)
target_link_libraries(android_content_pm_core PUBLIC android_framework_headers android_content_core)
