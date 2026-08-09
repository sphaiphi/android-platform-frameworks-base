# Package-info header generation
# Scans core/java/ for package-info.java files and generates C++ headers

# Find all package-info.java files under core/java
file(GLOB_RECURSE PACKAGE_INFO_JAVA_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../java/**/package-info.java"
)

# Generate output paths for each package-info.java
set(GENERATED_HEADERS "")
foreach(java_file ${PACKAGE_INFO_JAVA_FILES})
    # Skip package-info.java files in com.android.internal
    if(${java_file} MATCHES "com/android/internal")
        continue()
    endif()

    # Convert path: core/java/android/foo/bar/package-info.java
    # -> core/cpp/include/android/foo/bar/package-info.h
    file(RELATIVE_PATH rel_path
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../java"
        ${java_file}
    )
    # android/foo/bar/package-info.java -> android/foo/bar/package-info
    get_filename_component(rel_dir "${rel_path}" DIRECTORY)
    get_filename_component(rel_name "${rel_path}" NAME_WE)

    set(output_header "${CMAKE_CURRENT_SOURCE_DIR}/${rel_dir}/${rel_name}.h")
    list(APPEND GENERATED_HEADERS "${output_header}")

    add_custom_command(
        OUTPUT "${output_header}"
        COMMAND ${CMAKE_COMMAND} -E echo "Generating ${rel_dir}/${rel_name}.h"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${rel_dir}"
        DEPENDS ${java_file}
        COMMENT "Generating ${rel_dir}/${rel_name}.h from ${rel_path}"
        VERBATIM
    )
endforeach()

# If no headers were generated (e.g., all filtered out), create a dummy target
if(GENERATED_HEADERS)
    add_custom_target(generate_package_info_headers
        DEPENDS ${GENERATED_HEADERS}
    )
endif()

# Header-only library for package info
add_library(android_framework_headers INTERFACE)
target_include_directories(android_framework_headers INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)

# Add content/pm/ subdirectory for PackageInfo header
add_subdirectory(content/pm)
