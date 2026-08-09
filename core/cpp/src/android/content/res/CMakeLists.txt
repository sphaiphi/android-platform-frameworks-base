# Android framework content/res implementation

add_library(android_content_res_core
    AssetManager.cpp
    Configuration.cpp
    Resources.cpp
)
target_include_directories(android_content_res_core PUBLIC ../../../../include)
target_link_libraries(android_content_res_core PUBLIC android_framework_headers android_content_core)
