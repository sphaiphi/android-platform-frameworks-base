#pragma once

#include <cstdint>

namespace android::view {

class ViewConfiguration {
public:
    static auto get_scroll_bar_size() -> int32_t;
    static auto get_pressed_state_duration() -> int32_t;
    static auto get_long_press_timeout() -> int32_t;

private:
    static constexpr int32_t SCROLL_BAR_SIZE = 4;
    static constexpr int32_t PRESSED_STATE_DURATION = 64;
    static constexpr int32_t DEFAULT_LONG_PRESS_TIMEOUT = 400;
};

} // namespace android::view
