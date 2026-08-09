# CMakeLists.txt for package_info_generator host tool

add_executable(package_info_generator
    main.cpp
    parser.cpp
    emitter.cpp
)

target_include_directories(package_info_generator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(package_info_generator PRIVATE cxx_std_23)
