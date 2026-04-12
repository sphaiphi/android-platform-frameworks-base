#pragma once

#include <cstdint>

namespace android::view {

class KeyEvent {
public:
    enum Action {
        ACTION_DOWN = 0,
        ACTION_UP = 1,
    };

    KeyEvent(Action action, int32_t key_code) : action_(action), key_code_(key_code) {}

    auto get_action() const -> Action { return action_; }
    auto get_key_code() const -> int32_t { return key_code_; }

private:
    Action action_;
    int32_t key_code_;
};

} // namespace android::view
