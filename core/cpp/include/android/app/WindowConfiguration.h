#pragma once

#include <android/graphics/Rect.h>
#include <cstdint>

namespace android::app {

/**
 * Class that encapsulates all windowing-related settings for a window container.
 */
class WindowConfiguration {
public:
    enum WindowingMode {
        WINDOWING_MODE_UNDEFINED = 0,
        WINDOWING_MODE_FULLSCREEN = 1,
        WINDOWING_MODE_PINNED = 2,
        WINDOWING_MODE_FREEFORM = 5,
        WINDOWING_MODE_MULTI_WINDOW = 6
    };

    enum ActivityType {
        ACTIVITY_TYPE_UNDEFINED = 0,
        ACTIVITY_TYPE_STANDARD = 1,
        ACTIVITY_TYPE_HOME = 2,
        ACTIVITY_TYPE_RECENTS = 3,
        ACTIVITY_TYPE_ASSISTANT = 4,
        ACTIVITY_TYPE_DREAM = 5
    };

    WindowConfiguration() = default;

    auto set_bounds(const android::graphics::Rect& rect) -> void { bounds_ = rect; }
    [[nodiscard]] auto get_bounds() const noexcept -> const android::graphics::Rect& { return bounds_; }

    auto set_windowing_mode(WindowingMode mode) -> void { windowing_mode_ = mode; }
    [[nodiscard]] auto get_windowing_mode() const noexcept -> WindowingMode { return windowing_mode_; }

    auto set_activity_type(ActivityType type) -> void { activity_type_ = type; }
    [[nodiscard]] auto get_activity_type() const noexcept -> ActivityType { return activity_type_; }

private:
    android::graphics::Rect bounds_;
    WindowingMode windowing_mode_{WINDOWING_MODE_UNDEFINED};
    ActivityType activity_type_{ACTIVITY_TYPE_UNDEFINED};
};

} // namespace android::app
