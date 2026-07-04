#pragma once

#include <android/view/View.h>
#include <android/view/LayoutParams.h>
#include <vector>
#include <memory>

namespace android::view {

template <typename TLayoutParams = MarginLayoutParams>
class ViewGroup : public View,
                  public ViewParentMixin<ViewGroup<TLayoutParams>>,
                  public ViewManagerMixin<ViewGroup<TLayoutParams>> {
    // Grant CRTP mixins access to protected members.
    friend class ViewParentMixin<ViewGroup<TLayoutParams>>;
    friend class ViewManagerMixin<ViewGroup<TLayoutParams>>;

public:
    using LayoutParamsType = TLayoutParams;
    using MarginLayoutParamsType = MarginLayoutParams;

    ViewGroup() = default;
    virtual ~ViewGroup() = default;

    [[nodiscard]] auto get_child_count() const -> int32_t { return static_cast<int32_t>(children_.size()); }
    [[nodiscard]] std::shared_ptr<View> get_child_at(int32_t index) const;
    [[nodiscard]] const std::vector<std::shared_ptr<View>>& get_children() const { return children_; }

    void add_view(const std::shared_ptr<View>& child);
    void add_view(const std::shared_ptr<View>& child, const std::shared_ptr<TLayoutParams>& params);
    void remove_view(const std::shared_ptr<View>& child);
    void remove_view_at(int32_t index);
    void remove_all_views();

    void update_view_layout(const std::shared_ptr<View>& child, const std::shared_ptr<TLayoutParams>& params);

    bool dispatch_touch_event(const MotionEvent& event) override;
    bool dispatch_pointer_event(const MotionEvent& event);
    virtual bool on_intercept_touch_event(const MotionEvent& event);
    [[nodiscard]] bool bounds_overlap(float x, float y) const;

    void clear_focus() override;

    void measure_children(int32_t width_spec, int32_t height_spec);
    void layout_children();

    [[nodiscard]] bool is_clip_children() const {
        return (group_flags_ & static_cast<uint32_t>(ViewGroupFlags::CLIP_CHILDREN)) != 0; }
    void set_clip_children(bool clip) {
        if (clip) group_flags_ |= static_cast<uint32_t>(ViewGroupFlags::CLIP_CHILDREN);
        else group_flags_ &= ~static_cast<uint32_t>(ViewGroupFlags::CLIP_CHILDREN);
    }
    [[nodiscard]] bool is_clip_to_padding() const {
        return (group_flags_ & static_cast<uint32_t>(ViewGroupFlags::CLIP_TO_PADDING)) != 0; }
    void set_clip_to_padding(bool clip) {
        if (clip) group_flags_ |= static_cast<uint32_t>(ViewGroupFlags::CLIP_TO_PADDING);
        else group_flags_ &= ~static_cast<uint32_t>(ViewGroupFlags::CLIP_TO_PADDING);
    }
    [[nodiscard]] DescendantFocusability get_descendant_focusability() const { return descendant_focusability_; }
    void set_descendant_focusability(DescendantFocusability focusability) { descendant_focusability_ = focusability; }

    void request_disallow_intercept_touch_event(bool disallow) { disallow_intercept_ = disallow; }

    static auto get_child_measure_spec(int32_t spec, int32_t padding, int32_t child_dimension) -> int32_t;

protected:
    void on_layout(bool changed, int32_t left, int32_t top, int32_t right, int32_t bottom) override;
    void on_measure(int32_t width_measure_spec, int32_t height_measure_spec) override;
    void dispatch_draw(android::graphics::Canvas& canvas) override;

    virtual auto generate_default_layout_params() -> std::shared_ptr<LayoutParams>;

    // CRTP accessor override: ViewGroup's parent is a View* (from View base).
    [[nodiscard]] auto on_get_parent() const -> View* override { return View::on_get_parent(); }

private:
    std::vector<std::shared_ptr<View>> children_;
    std::vector<std::shared_ptr<TLayoutParams>> child_params_;
    View* touch_target_{nullptr};
    uint32_t group_flags_{static_cast<uint32_t>(ViewGroupFlags::CLIP_CHILDREN) | static_cast<uint32_t>(ViewGroupFlags::CLIP_TO_PADDING)};
    DescendantFocusability descendant_focusability_{DescendantFocusability::FOCUS_BEFORE_DESCENDANTS};
    bool disallow_intercept_{false};
    bool touch_intercepted_{false};
};

} // namespace android::view
