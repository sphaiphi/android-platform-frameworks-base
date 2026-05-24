#pragma once

#include <android/view/ViewGroup.h>
#include <android/view/Gravity.h>

namespace android::widget {

class FrameLayout : public android::view::ViewGroup {
public:
    class LayoutParams : public android::view::ViewGroup::MarginLayoutParams {
    public:
        int32_t gravity{android::view::Gravity::NO_GRAVITY};

        LayoutParams(int32_t w, int32_t h) : MarginLayoutParams(w, h) {}
        LayoutParams(int32_t w, int32_t h, int32_t g) : MarginLayoutParams(w, h), gravity(g) {}
    };

    FrameLayout() = default;
    virtual ~FrameLayout() = default;

protected:
    void on_measure(int32_t width_measure_spec, int32_t height_measure_spec) override;
    void on_layout(bool changed, int32_t left, int32_t top, int32_t right, int32_t bottom) override;

    auto generate_default_layout_params() -> std::shared_ptr<android::view::LayoutParams> override {
        return std::make_shared<LayoutParams>(LayoutParams::WRAP_CONTENT, LayoutParams::WRAP_CONTENT);
    }
};

} // namespace android::widget
