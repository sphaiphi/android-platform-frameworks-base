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
    AidlIntegration_test.cpp
    ViewConfiguration_test.cpp
    DisplayInfo_test.cpp
    View_test.cpp
    ViewGroup_test.cpp
    LayoutParams_test.cpp
    LinearLayout_test.cpp
    FrameLayout_test.cpp
    RelativeLayout_test.cpp
    TextView_test.cpp
    Layout_test.cpp
    Window_test.cpp
    ViewRootImpl_test.cpp
    Drawing_test.cpp
    Input_test.cpp
    Bundle_test.cpp
    ComponentName_test.cpp
    ClipData_test.cpp
    Rect_test.cpp
    Uri_test.cpp
    Intent_test.cpp
    IntentFilter_test.cpp
    PatternMatcher_test.cpp
    Activity_test.cpp
    ActivityClient_test.cpp
    ActivityManager_test.cpp
    ActivityTaskManager_test.cpp
    AppOpsManager_test.cpp
    TaskStackListener_test.cpp
    Exception_test.cpp
    InfoConfig_test.cpp
    OptionAction_test.cpp
    Notification_test.cpp
    SupportingClasses_test.cpp
    LifecycleStress_test.cpp
    NativeActivity_test.cpp
    ContextImpl_test.cpp
    ActivityThread_test.cpp
    Instrumentation_test.cpp
    Application_test.cpp
    LegacyActivities_test.cpp
)

target_link_libraries(framework_tests PRIVATE gtest_main android_framework_core)

include(GoogleTest)
if(NOT CMAKE_CROSSCOMPILING)
    gtest_discover_tests(framework_tests)
endif()
