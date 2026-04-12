#include <android/view/View.h>
#include <android/graphics/Canvas.h>

namespace android::view {

void View::layout(int32_t l, int32_t t, int32_t r, int32_t b) {
    bool changed = (l != left_ || t != top_ || r != right_ || b != bottom_);
    left_ = l;
    top_ = t;
    right_ = r;
    bottom_ = b;
    on_layout(changed, l, t, r, b);
}

void View::on_layout(bool /*changed*/, int32_t /*left*/, int32_t /*top*/, int32_t /*right*/, int32_t /*bottom*/) {
    // Base implementation does nothing
}

void View::measure(int32_t width_measure_spec, int32_t height_measure_spec) {
    on_measure(width_measure_spec, height_measure_spec);
}

void View::on_measure(int32_t width_measure_spec, int32_t height_measure_spec) {
    set_measured_dimension(MeasureSpec::get_size(width_measure_spec), 
                           MeasureSpec::get_size(height_measure_spec));
}

void View::set_measured_dimension(int32_t measured_width, int32_t measured_height) {
    measured_width_ = measured_width;
    measured_height_ = measured_height;
}

void View::draw(android::graphics::Canvas& canvas) {
    on_draw(canvas);
    dispatch_draw(canvas);
}

void View::on_draw(android::graphics::Canvas& /*canvas*/) {
    // Base implementation does nothing
}

void View::dispatch_draw(android::graphics::Canvas& /*canvas*/) {
    // Base implementation does nothing
}

bool View::dispatch_touch_event(const MotionEvent& event) {
    return on_touch_event(event);
}

bool View::dispatch_key_event(const KeyEvent& event) {
    return on_key_event(event);
}

bool View::on_touch_event(const MotionEvent& /*event*/) {
    return false;
}

bool View::on_key_event(const KeyEvent& /*event*/) {
    return false;
}

bool View::request_focus() {
    if (!focusable_ || visibility_ != VISIBLE) {
        return false;
    }
    if (focused_) return true;

    if (parent_) {
        parent_->clear_focus();
    }
    focused_ = true;
    return true;
}

void View::clear_focus() {
    focused_ = false;
}

} // namespace android::view
