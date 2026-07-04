#include <android/widget/FrameLayout.h>
#include <android/view/Gravity.h>
#include <algorithm>

namespace android::widget {

using namespace android::view;

void FrameLayout::on_measure(int32_t width_measure_spec, int32_t height_measure_spec) {
    int32_t max_width = 0;
    int32_t max_height = 0;
    
    for (int i = 0; i < get_child_count(); ++i) {
        auto child = get_child_at(i);
        if (child && child->get_visibility() != Visibility::Gone) {
            auto lp = child->get_layout_params();
            
            int32_t child_width_spec = get_child_measure_spec(width_measure_spec, 0, lp->width);
            int32_t child_height_spec = get_child_measure_spec(height_measure_spec, 0, lp->height);
            
            child->measure(child_width_spec, child_height_spec);
            
            max_width = std::max(max_width, child->get_measured_width());
            max_height = std::max(max_height, child->get_measured_height());
        }
    }
    
    set_measured_dimension(
        View::resolve_size(max_width, width_measure_spec),
        View::resolve_size(max_height, height_measure_spec)
    );
}

void FrameLayout::on_layout(bool changed, int32_t left, int32_t top, int32_t right, int32_t bottom) {
    int32_t parent_width = right - left;
    int32_t parent_height = bottom - top;

    for (int i = 0; i < get_child_count(); ++i) {
        auto child = get_child_at(i);
        if (child && child->get_visibility() != Visibility::Gone) {
            int32_t child_width = child->get_measured_width();
            int32_t child_height = child->get_measured_height();
            
            int32_t gravity = Gravity::TOP | Gravity::LEFT;
            auto lp = std::dynamic_pointer_cast<LayoutParams>(child->get_layout_params());
            if (lp && lp->gravity != Gravity::NO_GRAVITY) {
                gravity = lp->gravity;
            }

            int32_t child_left = 0;
            int32_t child_top = 0;

            // Horizontal alignment
            switch (gravity & Gravity::HORIZONTAL_GRAVITY_MASK) {
                case Gravity::CENTER_HORIZONTAL:
                    child_left = (parent_width - child_width) / 2;
                    break;
                case Gravity::RIGHT:
                    child_left = parent_width - child_width;
                    break;
                case Gravity::LEFT:
                default:
                    child_left = 0;
                    break;
            }

            // Vertical alignment
            switch (gravity & Gravity::VERTICAL_GRAVITY_MASK) {
                case Gravity::CENTER_VERTICAL:
                    child_top = (parent_height - child_height) / 2;
                    break;
                case Gravity::BOTTOM:
                    child_top = parent_height - child_height;
                    break;
                case Gravity::TOP:
                default:
                    child_top = 0;
                    break;
            }

            child->layout(child_left, child_top, child_left + child_width, child_top + child_height);
        }
    }
}

} // namespace android::widget
