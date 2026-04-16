#pragma once

#include <android/view/ViewGroup.h>

namespace android::widget {

class LinearLayout : public android::view::ViewGroup {
public:
    enum Orientation {
        HORIZONTAL = 0,
        VERTICAL = 1
    };

    LinearLayout() = default;
    virtual ~LinearLayout() = default;

    auto get_orientation() const -> Orientation { return orientation_; }
    void set_orientation(Orientation orientation) { orientation_ = orientation; }

protected:
    void on_measure(int32_t width_measure_spec, int32_t height_measure_spec) override;
    void on_layout(bool changed, int32_t left, int32_t top, int32_t right, int32_t bottom) override;

private:
    Orientation orientation_{HORIZONTAL};

    void measure_vertical(int32_t width_measure_spec, int32_t height_measure_spec);
    void measure_horizontal(int32_t width_measure_spec, int32_t height_measure_spec);
    
    void layout_vertical(int32_t left, int32_t top, int32_t right, int32_t bottom);
    void layout_horizontal(int32_t left, int32_t top, int32_t right, int32_t bottom);
};

} // namespace android::widget
