#pragma once

#include <cstdint>

namespace android::view {

class MotionEvent {
public:
    enum Action {
        ACTION_DOWN = 0,
        ACTION_UP = 1,
        ACTION_MOVE = 2,
        ACTION_CANCEL = 3,
    };

    MotionEvent(Action action, float x, float y) : action_(action), x_(x), y_(y) {}

    auto get_action() const -> Action { return action_; }
    auto get_x() const -> float { return x_; }
    auto get_y() const -> float { return y_; }

    void offset_location(float dx, float dy) {
        x_ += dx;
        y_ += dy;
    }

private:
    Action action_;
    float x_;
    float y_;
};

} // namespace android::view
