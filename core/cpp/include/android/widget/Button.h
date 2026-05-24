#pragma once

#include <android/widget/TextView.h>
#include <functional>

namespace android::widget {

class Button : public TextView {
public:
    using OnClickListener = std::function<void(View*)>;

    Button() = default;
    virtual ~Button() = default;

    void set_on_click_listener(OnClickListener listener) {
        on_click_listener_ = std::move(listener);
    }

    bool on_touch_event(const android::view::MotionEvent& event) override;

private:
    OnClickListener on_click_listener_;
    bool is_pressed_{false};
};

} // namespace android::widget
