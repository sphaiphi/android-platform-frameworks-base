#include <android/widget/TextView.h>
#include <android/graphics/Canvas.h>

namespace android::widget {

using namespace android::view;

void TextView::on_measure(int32_t width_measure_spec, int32_t height_measure_spec) {
    int32_t width = static_cast<int32_t>(text_.length() * 10);
    int32_t height = 20;

    int32_t width_mode = MeasureSpec::get_mode(width_measure_spec);
    int32_t width_size = MeasureSpec::get_size(width_measure_spec);
    int32_t height_mode = MeasureSpec::get_mode(height_measure_spec);
    int32_t height_size = MeasureSpec::get_size(height_measure_spec);

    int32_t final_width = (width_mode == MeasureSpec::EXACTLY) ? width_size : width;
    int32_t final_height = (height_mode == MeasureSpec::EXACTLY) ? height_size : height;

    set_measured_dimension(final_width, final_height);
}

void TextView::on_draw(android::graphics::Canvas& canvas) {
    // Placeholder for text rendering logic
    // canvas.drawText(text_, ...);
}

} // namespace android::widget
