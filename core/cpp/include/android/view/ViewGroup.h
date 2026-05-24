#pragma once

#include <android/view/View.h>
#include <android/view/LayoutParams.h>
#include <vector>
#include <memory>

namespace android::view {

class ViewGroup : public View {
public:
    using LayoutParams = android::view::LayoutParams;
    using MarginLayoutParams = android::view::MarginLayoutParams;

    ViewGroup() = default;
    virtual ~ViewGroup() = default;

    auto get_child_count() const -> int32_t { return static_cast<int32_t>(children_.size()); }
    auto get_child_at(int32_t index) const -> std::shared_ptr<View>;
    auto get_children() const -> const std::vector<std::shared_ptr<View>>&;

    void add_view(const std::shared_ptr<View>& child);
    void add_view(const std::shared_ptr<View>& child, const std::shared_ptr<LayoutParams>& params);
    void remove_view(const std::shared_ptr<View>& child);
    void remove_view_at(int32_t index);
    void remove_all_views();

    bool dispatch_touch_event(const MotionEvent& event) override;
    bool dispatch_pointer_event(const MotionEvent& event);
    virtual bool on_intercept_touch_event(const MotionEvent& event);
    bool bounds_overlap(float x, float y) const;

    void clear_focus() override;

    static auto get_child_measure_spec(int32_t spec, int32_t padding, int32_t child_dimension) -> int32_t;

protected:
    void on_layout(bool changed, int32_t left, int32_t top, int32_t right, int32_t bottom) override;
    void on_measure(int32_t width_measure_spec, int32_t height_measure_spec) override;
    void dispatch_draw(android::graphics::Canvas& canvas) override;

    virtual auto generate_default_layout_params() -> std::shared_ptr<LayoutParams>;

private:
    std::vector<std::shared_ptr<View>> children_;
};

} // namespace android::view
