#include <android/view/ViewGroup.h>
#include <android/graphics/Canvas.h>
#include <algorithm>

namespace android::view {

// ============================================================================
// Template implementations
// ============================================================================

template <typename TLayoutParams>
auto ViewGroup<TLayoutParams>::get_child_at(int32_t index) const -> std::shared_ptr<View> {
    if (index < 0 || index >= static_cast<int32_t>(children_.size())) {
        return nullptr;
    }
    return children_[index];
}

template <typename TLayoutParams>
void ViewGroup<TLayoutParams>::add_view(const std::shared_ptr<View>& child) {
    if (child == nullptr) return;
    auto params = child->get_layout_params();
    if (params == nullptr) {
        params = generate_default_layout_params();
    }
    add_view(child, std::static_pointer_cast<TLayoutParams>(params));
}

template <typename TLayoutParams>
void ViewGroup<TLayoutParams>::add_view(const std::shared_ptr<View>& child, const std::shared_ptr<TLayoutParams>& params) {
    if (child == nullptr || child.get() == this) return;

    // Reparenting: remove from old parent first
    if (child->get_parent() != nullptr) {
        auto old_parent = static_cast<ViewGroup*>(child->get_parent());
        if (old_parent != this) {
            old_parent->remove_view(child);
        }
    }

    child->set_layout_params(params);
    children_.push_back(child);
    child_params_.push_back(params);
    child->set_parent(this);
    request_layout();
}

template <typename TLayoutParams>
void ViewGroup<TLayoutParams>::remove_view(const std::shared_ptr<View>& child) {
    if (child == nullptr) return;
    auto it = std::find(children_.begin(), children_.end(), child);
    if (it != children_.end()) {
        child->set_parent(nullptr);
        children_.erase(it);
        if (child_params_.size() > static_cast<size_t>(std::distance(children_.begin(), it))) {
            child_params_.erase(child_params_.begin() + std::distance(children_.begin(), it));
        }
        request_layout();
    }
}

template <typename TLayoutParams>
void ViewGroup<TLayoutParams>::remove_view_at(int32_t index) {
    if (index < 0 || index >= static_cast<int32_t>(children_.size())) {
        return;
    }
    auto child = children_[index];
    child->set_parent(nullptr);
    children_.erase(children_.begin() + index);
    if (child_params_.size() > static_cast<size_t>(index)) {
        child_params_.erase(child_params_.begin() + index);
    }
    request_layout();
}

template <typename TLayoutParams>
void ViewGroup<TLayoutParams>::remove_all_views() {
    for (auto& child : children_) {
        child->set_parent(nullptr);
    }
    children_.clear();
    child_params_.clear();
    request_layout();
}

template <typename TLayoutParams>
void ViewGroup<TLayoutParams>::update_view_layout(const std::shared_ptr<View>& child, const std::shared_ptr<TLayoutParams>& params) {
    if (child == nullptr || params == nullptr) return;
    auto it = std::find(children_.begin(), children_.end(), child);
    if (it != children_.end()) {
        size_t idx = std::distance(children_.begin(), it);
        child->set_layout_params(params);
        if (idx < child_params_.size()) {
            child_params_[idx] = params;
        }
        request_layout();
    }
}

template <typename TLayoutParams>
void ViewGroup<TLayoutParams>::on_layout(bool changed, int32_t left, int32_t top, int32_t right, int32_t bottom) {
    if (changed) {
        layout_children();
    }
}

template <typename TLayoutParams>
void ViewGroup<TLayoutParams>::on_measure(int32_t width_measure_spec, int32_t height_measure_spec) {
    measure_children(width_measure_spec, height_measure_spec);
}

template <typename TLayoutParams>
void ViewGroup<TLayoutParams>::dispatch_draw(android::graphics::Canvas& canvas) {
    // Draw children in z-order (back to front: index 0 to N-1)
    if (is_clip_children()) {
        canvas.save();
        canvas.clipRect(static_cast<float>(get_left()), static_cast<float>(get_top()),
                        static_cast<float>(get_right()), static_cast<float>(get_bottom()));
    }

    for (int i = 0; i < get_child_count(); ++i) {
        auto child = get_child_at(i);
        if (child && child->get_visibility() != Visibility::Gone) {
            child->draw(canvas);
        }
    }

    if (is_clip_children()) {
        canvas.restore();
    }
}

template <typename TLayoutParams>
bool ViewGroup<TLayoutParams>::dispatch_touch_event(const MotionEvent& event) {
    // Check disallow_intercept_ — if true, skip intercept check
    if (!disallow_intercept_ && !touch_intercepted_) {
        if (on_intercept_touch_event(event)) {
            touch_intercepted_ = true;
            return on_touch_event(event);
        }
    }

    // If this is an ACTION_DOWN, reset touch_intercepted_ and clear old target
    if (event.get_action() == 0x00000000) { // ACTION_DOWN
        touch_intercepted_ = false;
        touch_target_ = nullptr;
    }

    // Iterate children in reverse z-order (front-to-back)
    for (int i = static_cast<int>(children_.size()) - 1; i >= 0; --i) {
        auto child = children_[i];
        if (child == nullptr || child->get_visibility() != Visibility::Visible) continue;

        float x = event.get_x();
        float y = event.get_y();

        if (x >= static_cast<float>(child->get_left()) && x < static_cast<float>(child->get_right()) &&
            y >= static_cast<float>(child->get_top()) && y < static_cast<float>(child->get_bottom())) {

            MotionEvent transformed_event = event;
            transformed_event.offset_location(-static_cast<float>(child->get_left()),
                                              -static_cast<float>(child->get_top()));

            if (child->dispatch_touch_event(transformed_event)) {
                touch_target_ = child.get();
                return true;
            }
        }
    }

    // Fall back to View::dispatch_touch_event
    return View::dispatch_touch_event(event);
}

template <typename TLayoutParams>
bool ViewGroup<TLayoutParams>::on_intercept_touch_event(const MotionEvent& /*event*/) {
    return false;
}

template <typename TLayoutParams>
void ViewGroup<TLayoutParams>::measure_children(int32_t width_spec, int32_t height_spec) {
    int32_t padding_left = get_padding_left();
    int32_t padding_top = get_padding_top();
    int32_t padding_right = get_padding_right();
    int32_t padding_bottom = get_padding_bottom();
    int32_t width_size = static_cast<int32_t>(MeasureSpec::get_size(static_cast<uint32_t>(width_spec)));
    int32_t height_size = static_cast<int32_t>(MeasureSpec::get_size(static_cast<uint32_t>(height_spec)));

    for (int i = 0; i < get_child_count(); ++i) {
        auto child = get_child_at(i);
        if (child == nullptr || child->get_visibility() == Visibility::Gone) continue;

        auto child_params = (i < static_cast<int32_t>(child_params_.size())) ? child_params_[i] : nullptr;
        int32_t child_w = (child_params) ? child_params->width : LayoutParams::WRAP_CONTENT;
        int32_t child_h = (child_params) ? child_params->height : LayoutParams::WRAP_CONTENT;

        int32_t child_width_spec = get_child_measure_spec(width_spec, padding_left + padding_right, child_w);
        int32_t child_height_spec = get_child_measure_spec(height_spec, padding_top + padding_bottom, child_h);

        child->measure(child_width_spec, child_height_spec);
    }

    // Set measured dimension based on parent constraints
    set_measured_dimension(width_size, height_size);
}

template <typename TLayoutParams>
void ViewGroup<TLayoutParams>::layout_children() {
    for (int i = 0; i < get_child_count(); ++i) {
        auto child = get_child_at(i);
        if (child == nullptr || child->get_visibility() == Visibility::Gone) continue;

        auto child_params = (i < static_cast<int32_t>(child_params_.size())) ? child_params_[i] : nullptr;

        int32_t child_left = get_padding_left();
        int32_t child_top = get_padding_top();

        if (child_params) {
            child_left += static_cast<int32_t>(child_params->width);
            child_top += static_cast<int32_t>(child_params->height);
        }

        child->layout(child_left, child_top,
                      child_left + get_width(), child_top + get_height());
    }
}

template <typename TLayoutParams>
bool ViewGroup<TLayoutParams>::bounds_overlap(float x, float y) const {
    return x >= static_cast<float>(get_left()) && x < static_cast<float>(get_right()) &&
           y >= static_cast<float>(get_top()) && y < static_cast<float>(get_bottom());
}

template <typename TLayoutParams>
void ViewGroup<TLayoutParams>::clear_focus() {
    View::clear_focus();
    for (auto& child : children_) {
        child->clear_focus();
    }
}

template <typename TLayoutParams>
auto ViewGroup<TLayoutParams>::generate_default_layout_params() -> std::shared_ptr<LayoutParams> {
    return std::static_pointer_cast<LayoutParams>(std::make_shared<TLayoutParams>(LayoutParams::WRAP_CONTENT, LayoutParams::WRAP_CONTENT));
}

template <typename TLayoutParams>
bool ViewGroup<TLayoutParams>::dispatch_pointer_event(const MotionEvent& event) {
    if (!disallow_intercept_ && !touch_intercepted_ && on_intercept_touch_event(event)) {
        touch_intercepted_ = true;
        return on_touch_event(event);
    }

    for (int i = static_cast<int>(children_.size()) - 1; i >= 0; --i) {
        auto child = children_[i];
        if (child == nullptr || child->get_visibility() != Visibility::Visible) continue;

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

template <typename TLayoutParams>
auto ViewGroup<TLayoutParams>::get_child_measure_spec(int32_t spec, int32_t padding, int32_t child_dimension) -> int32_t {
    uint32_t spec_mode = MeasureSpec::get_mode(static_cast<uint32_t>(spec));
    uint32_t spec_size = MeasureSpec::get_size(static_cast<uint32_t>(spec));

    int32_t size = std::max(0, static_cast<int32_t>(spec_size) - padding);

    uint32_t result_size = 0;
    uint32_t result_mode = 0;

    switch (spec_mode) {
    case MeasureSpec::EXACTLY:
        if (child_dimension >= 0) {
            result_size = static_cast<uint32_t>(child_dimension);
            result_mode = MeasureSpec::EXACTLY;
        } else if (child_dimension == LayoutParams::MATCH_PARENT) {
            result_size = static_cast<uint32_t>(size);
            result_mode = MeasureSpec::EXACTLY;
        } else if (child_dimension == LayoutParams::WRAP_CONTENT) {
            result_size = static_cast<uint32_t>(size);
            result_mode = MeasureSpec::AT_MOST;
        }
        break;

    case MeasureSpec::AT_MOST:
        if (child_dimension >= 0) {
            result_size = static_cast<uint32_t>(child_dimension);
            result_mode = MeasureSpec::EXACTLY;
        } else if (child_dimension == LayoutParams::MATCH_PARENT) {
            result_size = static_cast<uint32_t>(size);
            result_mode = MeasureSpec::AT_MOST;
        } else if (child_dimension == LayoutParams::WRAP_CONTENT) {
            result_size = static_cast<uint32_t>(size);
            result_mode = MeasureSpec::AT_MOST;
        }
        break;

    case MeasureSpec::UNSPECIFIED:
        if (child_dimension >= 0) {
            result_size = static_cast<uint32_t>(child_dimension);
            result_mode = MeasureSpec::EXACTLY;
        } else if (child_dimension == LayoutParams::MATCH_PARENT) {
            result_size = 0;
            result_mode = MeasureSpec::UNSPECIFIED;
        } else if (child_dimension == LayoutParams::WRAP_CONTENT) {
            result_size = 0;
            result_mode = MeasureSpec::UNSPECIFIED;
        }
        break;
    }
    return static_cast<int32_t>(MeasureSpec::make(result_size, result_mode));
}

// Explicit template instantiation
template class ViewGroup<MarginLayoutParams>;

} // namespace android::view
