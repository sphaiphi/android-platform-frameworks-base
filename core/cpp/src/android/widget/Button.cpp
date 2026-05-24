#include <android/widget/Button.h>
#include <android/view/MotionEvent.h>

namespace android::widget {

using namespace android::view;

bool Button::on_touch_event(const MotionEvent& event) {
    switch (event.get_action()) {
        case MotionEvent::ACTION_DOWN:
            is_pressed_ = true;
            return true;
        case MotionEvent::ACTION_UP:
            if (is_pressed_) {
                is_pressed_ = false;
                if (on_click_listener_) {
                    on_click_listener_(this);
                }
                return true;
            }
            break;
        case MotionEvent::ACTION_CANCEL:
            is_pressed_ = false;
            break;
    }
    return TextView::on_touch_event(event);
}

} // namespace android::widget
