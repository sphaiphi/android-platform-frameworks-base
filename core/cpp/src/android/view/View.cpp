#include <android/view/View.h>
#include <android/graphics/Canvas.h>
#include <android/graphics/Drawable.h>

namespace android::view {

void View::set_visibility(Visibility visibility) {
    bool was_gone = (visibility_ == Visibility::Gone);
    bool will_gone = (visibility == Visibility::Gone);
    visibility_ = visibility;
    if (was_gone != will_gone) {
        request_layout();
    }
}

void View::layout(int32_t l, int32_t t, int32_t r, int32_t b) {
    bool changed = (l != left_ || t != top_ || r != right_ || b != bottom_);
    left_ = l;
    top_ = t;
    right_ = r;
    bottom_ = b;
    layoutRequested_ = false;
    on_layout(changed, l, t, r, b);
}

void View::measure(int32_t width_measure_spec, int32_t height_measure_spec) {
    measured_ = true;
    on_measure(width_measure_spec, height_measure_spec);
}

void View::on_measure(int32_t width_measure_spec, int32_t height_measure_spec) {
    set_measured_dimension(MeasureSpec::get_size(static_cast<uint32_t>(width_measure_spec)),
                           MeasureSpec::get_size(static_cast<uint32_t>(height_measure_spec)));
}

void View::set_measured_dimension(int32_t measured_width, int32_t measured_height) {
    measured_width_ = measured_width;
    measured_height_ = measured_height;
}

void View::draw(android::graphics::Canvas& canvas) {
    if (visibility_ == Visibility::Gone) return;
    if (background_) {
        background_->draw(&canvas);
    }
    on_draw(canvas);
    dispatch_draw(canvas);
}

void View::set_background(std::shared_ptr<android::graphics::Drawable> bg) {
    background_ = std::move(bg);
}

std::shared_ptr<android::graphics::Drawable> View::get_background() const {
    return background_;
}

auto View::resolve_size(int32_t size, int32_t measure_spec) -> int32_t {
    uint32_t spec_mode = MeasureSpec::get_mode(static_cast<uint32_t>(measure_spec));
    uint32_t spec_size = MeasureSpec::get_size(static_cast<uint32_t>(measure_spec));

    int32_t result = size;
    switch (spec_mode) {
    case MeasureSpec::UNSPECIFIED:
        result = size;
        break;
    case MeasureSpec::AT_MOST:
        if (spec_size < static_cast<uint32_t>(size)) {
            result = static_cast<int32_t>(spec_size);
        } else {
            result = size;
        }
        break;
    case MeasureSpec::EXACTLY:
        result = static_cast<int32_t>(spec_size);
        break;
    }
    return result;
}

void View::on_layout(bool /*changed*/, int32_t /*l*/, int32_t /*t*/, int32_t /*r*/, int32_t /*b*/) {}
void View::on_draw(android::graphics::Canvas& /*canvas*/) {}
void View::dispatch_draw(android::graphics::Canvas& /*canvas*/) {}

bool View::dispatch_touch_event(const MotionEvent& event) {
    return on_touch_event(event);
}

bool View::dispatch_pointer_event(const MotionEvent& event) {
    return dispatch_touch_event(event);
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
    if (!is_focusable() || visibility_ != Visibility::Visible) {
        return false;
    }
    if (focused_) return true;

    if (parent_) {
        parent_->clear_focus();
    }
    focused_ = true;

    // Propagate via ViewParentMixin (pure CRTP, no explicit parent param)
    request_child_focus(this, this);

    return true;
}

void View::clear_focus() {
    focused_ = false;
}

void View::request_layout() {
    ViewParentMixin<View>::request_layout();
}

void View::invalidate() {
    ViewParentMixin<View>::on_descendant_invalidated(this, this);
}

} // namespace android::view
