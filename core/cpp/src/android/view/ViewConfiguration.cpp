#include <android/view/ViewConfiguration.h>

namespace android::view {

auto ViewConfiguration::get_scroll_bar_size() -> int32_t {
    return SCROLL_BAR_SIZE;
}

auto ViewConfiguration::get_pressed_state_duration() -> int32_t {
    return PRESSED_STATE_DURATION;
}

auto ViewConfiguration::get_long_press_timeout() -> int32_t {
    return DEFAULT_LONG_PRESS_TIMEOUT;
}

} // namespace android::view
