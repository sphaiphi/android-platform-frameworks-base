#pragma once

#include <android/view/ViewGroup.h>
#include <android/view/Gravity.h>

namespace android::widget {

class LinearLayout : public android::view::ViewGroup<android::view::MarginLayoutParams> {
public:
    enum Orientation {
        HORIZONTAL = 0,
        VERTICAL = 1
    };

    class LayoutParams : public android::view::MarginLayoutParams {
    public:
        float weight{0.0f};
        int32_t gravity{-1};

        LayoutParams(int32_t w, int32_t h) : MarginLayoutParams(w, h) {}
        LayoutParams(int32_t w, int32_t h, float wt) : MarginLayoutParams(w, h), weight(wt) {}
    };

    LinearLayout() = default;
    virtual ~LinearLayout() = default;

    auto get_orientation() const -> Orientation { return orientation_; }
    void set_orientation(Orientation orientation) { orientation_ = orientation; }

    auto get_gravity() const -> int32_t { return gravity_; }
    void set_gravity(int32_t gravity) { gravity_ = gravity; }

protected:
    void on_measure(int32_t width_measure_spec, int32_t height_measure_spec) override;
    void on_layout(bool changed, int32_t left, int32_t top, int32_t right, int32_t bottom) override;

    auto generate_default_layout_params() -> std::shared_ptr<android::view::LayoutParams> override {
        return std::make_shared<LayoutParams>(android::view::LayoutParams::WRAP_CONTENT, android::view::LayoutParams::WRAP_CONTENT);
    }

private:
    Orientation orientation_{HORIZONTAL};
    int32_t gravity_{android::view::Gravity::TOP | android::view::Gravity::LEFT};

    void measure_vertical(int32_t width_measure_spec, int32_t height_measure_spec);
    void measure_horizontal(int32_t width_measure_spec, int32_t height_measure_spec);
    
    void layout_vertical(int32_t left, int32_t top, int32_t right, int32_t bottom);
    void layout_horizontal(int32_t left, int32_t top, int32_t right, int32_t bottom);
};

} // namespace android::widget
