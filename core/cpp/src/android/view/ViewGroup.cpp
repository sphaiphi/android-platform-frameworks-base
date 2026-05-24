#include <android/view/ViewGroup.h>
#include <algorithm>

namespace android::view {

auto ViewGroup::get_child_at(int32_t index) const -> std::shared_ptr<View> {
    if (index < 0 || index >= static_cast<int32_t>(children_.size())) {
        return nullptr;
    }
    return children_[index];
}

void ViewGroup::add_view(const std::shared_ptr<View>& child) {
    if (child == nullptr) return;
    auto params = child->get_layout_params();
    if (params == nullptr) {
        params = generate_default_layout_params();
    }
    add_view(child, params);
}

void ViewGroup::add_view(const std::shared_ptr<View>& child, const std::shared_ptr<LayoutParams>& params) {
    if (child == nullptr || child.get() == this) return;
    
    if (child->get_parent() != nullptr) {
        // In a real implementation, we should remove from old parent
    }
    
    child->set_layout_params(params);
    children_.push_back(child);
    child->set_parent(this);
}

void ViewGroup::remove_view(const std::shared_ptr<View>& child) {
    if (child == nullptr) return;
    auto it = std::find(children_.begin(), children_.end(), child);
    if (it != children_.end()) {
        child->set_parent(nullptr);
        children_.erase(it);
    }
}

void ViewGroup::remove_view_at(int32_t index) {
    if (index < 0 || index >= static_cast<int32_t>(children_.size())) {
        return;
    }
    auto child = children_[index];
    child->set_parent(nullptr);
    children_.erase(children_.begin() + index);
}

void ViewGroup::remove_all_views() {
    for (auto& child : children_) {
        child->set_parent(nullptr);
    }
    children_.clear();
}

void ViewGroup::on_layout(bool changed, int32_t left, int32_t top, int32_t right, int32_t bottom) {
    // Default implementation does nothing
}

void ViewGroup::on_measure(int32_t width_measure_spec, int32_t height_measure_spec) {
    set_measured_dimension(width_measure_spec, height_measure_spec);
}

void ViewGroup::dispatch_draw(android::graphics::Canvas& canvas) {
    for (int i = 0; i < get_child_count(); ++i) {
        auto child = get_child_at(i);
        if (child && child->get_visibility() == VISIBLE) {
            child->draw(canvas);
        }
    }
}

bool ViewGroup::dispatch_touch_event(const MotionEvent& event) {
    bool intercepted = on_intercept_touch_event(event);
    if (!intercepted) {
        // Iterate in reverse Z-order
        for (int i = static_cast<int>(children_.size()) - 1; i >= 0; --i) {
            auto child = children_[i];
            if (child->get_visibility() != VISIBLE) continue;

            float x = event.get_x();
            float y = event.get_y();

            if (x >= child->get_left() && x < child->get_right() &&
                y >= child->get_top() && y < child->get_bottom()) {
                
                MotionEvent transformed_event = event;
                transformed_event.offset_location(-static_cast<float>(child->get_left()), 
                                                  -static_cast<float>(child->get_top()));
                
                if (child->dispatch_touch_event(transformed_event)) {
                    return true;
                }
            }
        }
    }
    return View::dispatch_touch_event(event);
}

bool ViewGroup::on_intercept_touch_event(const MotionEvent& /*event*/) {
    return false;
}

void ViewGroup::clear_focus() {
    View::clear_focus();
    for (auto& child : children_) {
        child->clear_focus();
    }
}

auto ViewGroup::get_child_measure_spec(int32_t spec, int32_t padding, int32_t child_dimension) -> int32_t {
    uint32_t spec_mode = View::MeasureSpec::get_mode(static_cast<uint32_t>(spec));
    uint32_t spec_size = View::MeasureSpec::get_size(static_cast<uint32_t>(spec));

    int32_t size = std::max(0, static_cast<int32_t>(spec_size) - padding);

    uint32_t result_size = 0;
    uint32_t result_mode = 0;

    switch (spec_mode) {
    case View::MeasureSpec::EXACTLY:
        if (child_dimension >= 0) {
            result_size = static_cast<uint32_t>(child_dimension);
            result_mode = View::MeasureSpec::EXACTLY;
        } else if (child_dimension == LayoutParams::MATCH_PARENT) {
            result_size = static_cast<uint32_t>(size);
            result_mode = View::MeasureSpec::EXACTLY;
        } else if (child_dimension == LayoutParams::WRAP_CONTENT) {
            result_size = static_cast<uint32_t>(size);
            result_mode = View::MeasureSpec::AT_MOST;
        }
        break;

    case View::MeasureSpec::AT_MOST:
        if (child_dimension >= 0) {
            result_size = static_cast<uint32_t>(child_dimension);
            result_mode = View::MeasureSpec::EXACTLY;
        } else if (child_dimension == LayoutParams::MATCH_PARENT) {
            result_size = static_cast<uint32_t>(size);
            result_mode = View::MeasureSpec::AT_MOST;
        } else if (child_dimension == LayoutParams::WRAP_CONTENT) {
            result_size = static_cast<uint32_t>(size);
            result_mode = View::MeasureSpec::AT_MOST;
        }
        break;

    case View::MeasureSpec::UNSPECIFIED:
        if (child_dimension >= 0) {
            result_size = static_cast<uint32_t>(child_dimension);
            result_mode = View::MeasureSpec::EXACTLY;
        } else if (child_dimension == LayoutParams::MATCH_PARENT) {
            result_size = 0;
            result_mode = View::MeasureSpec::UNSPECIFIED;
        } else if (child_dimension == LayoutParams::WRAP_CONTENT) {
            result_size = 0;
            result_mode = View::MeasureSpec::UNSPECIFIED;
        }
        break;
    }
    return static_cast<int32_t>(View::MeasureSpec::make_measure_spec(result_size, result_mode));
}

auto ViewGroup::generate_default_layout_params() -> std::shared_ptr<LayoutParams> {
    return std::make_shared<LayoutParams>(LayoutParams::WRAP_CONTENT, LayoutParams::WRAP_CONTENT);
}

auto ViewGroup::get_children() const -> const std::vector<std::shared_ptr<View>>& {
    return children_;
}

bool ViewGroup::bounds_overlap(float x, float y) const {
    return x >= static_cast<float>(get_left()) && x < static_cast<float>(get_right()) &&
           y >= static_cast<float>(get_top()) && y < static_cast<float>(get_bottom());
}

bool ViewGroup::dispatch_pointer_event(const MotionEvent& event) {
    if (on_intercept_touch_event(event)) {
        return on_touch_event(event);
    }
    for (int i = static_cast<int>(children_.size()) - 1; i >= 0; --i) {
        auto child = children_[i];
        if (child->get_visibility() != VISIBLE) continue;

        float x = event.get_x();
        float y = event.get_y();

        if (x >= static_cast<float>(child->get_left()) && x < static_cast<float>(child->get_right()) &&
            y >= static_cast<float>(child->get_top()) && y < static_cast<float>(child->get_bottom())) {

            MotionEvent transformed = event;
            transformed.offset_location(
                -static_cast<float>(child->get_left()),
                -static_cast<float>(child->get_top()));

            if (child->dispatch_pointer_event(transformed)) {
                return true;
            }
        }
    }
    return on_touch_event(event);
}

} // namespace android::view
