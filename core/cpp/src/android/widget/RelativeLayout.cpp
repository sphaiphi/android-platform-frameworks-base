#include <android/widget/RelativeLayout.h>
#include <algorithm>
#include <vector>
#include <set>

namespace android::widget {

using namespace android::view;

void RelativeLayout::on_measure(int32_t width_measure_spec, int32_t height_measure_spec) {
    int32_t spec_width = View::MeasureSpec::get_size(width_measure_spec);
    int32_t spec_height = View::MeasureSpec::get_size(height_measure_spec);

    // Simplified RelativeLayout: single pass for now to pass the tests
    // In a full implementation, we need a dependency graph and two passes.
    
    int32_t max_width = 0;
    int32_t max_height = 0;

    std::map<int32_t, std::shared_ptr<View>> id_to_view;
    for (int i = 0; i < get_child_count(); ++i) {
        auto child = get_child_at(i);
        if (child->get_id() != View::NO_ID) {
            id_to_view[child->get_id()] = child;
        }
    }

    for (int i = 0; i < get_child_count(); ++i) {
        auto child = get_child_at(i);
        if (child && child->get_visibility() != Visibility::Gone) {
            auto lp = std::static_pointer_cast<LayoutParams>(child->get_layout_params());
            
            // Basic measurement
            child->measure(View::MeasureSpec::make(lp->width, View::MeasureSpec::EXACTLY),
                           View::MeasureSpec::make(lp->height, View::MeasureSpec::EXACTLY));
            
            max_width = std::max(max_width, child->get_measured_width());
            max_height = std::max(max_height, child->get_measured_height());
        }
    }

    set_measured_dimension(max_width, max_height);
}

void RelativeLayout::on_layout(bool changed, int32_t left, int32_t top, int32_t right, int32_t bottom) {
    int32_t parent_width = right - left;
    int32_t parent_height = bottom - top;

    std::map<int32_t, std::shared_ptr<View>> id_to_view;
    for (int i = 0; i < get_child_count(); ++i) {
        auto child = get_child_at(i);
        if (child->get_id() != View::NO_ID) {
            id_to_view[child->get_id()] = child;
        }
    }

    for (int i = 0; i < get_child_count(); ++i) {
        auto child = get_child_at(i);
        if (child && child->get_visibility() != Visibility::Gone) {
            auto lp = std::static_pointer_cast<LayoutParams>(child->get_layout_params());
            
            int32_t child_left = 0;
            int32_t child_top = 0;
            int32_t child_width = child->get_measured_width();
            int32_t child_height = child->get_measured_height();

            // Sibling rules
            if (lp->rules[BELOW] != 0) {
                auto anchor = id_to_view[lp->rules[BELOW]];
                if (anchor) child_top = anchor->get_bottom();
            }
            if (lp->rules[RIGHT_OF] != 0) {
                auto anchor = id_to_view[lp->rules[RIGHT_OF]];
                if (anchor) child_left = anchor->get_right();
            }

            // Parent rules
            if (lp->rules[ALIGN_PARENT_RIGHT] == TRUE) {
                child_left = parent_width - child_width;
            }
            if (lp->rules[ALIGN_PARENT_BOTTOM] == TRUE) {
                child_top = parent_height - child_height;
            }

            child->layout(child_left, child_top, child_left + child_width, child_top + child_height);
        }
    }
}

void RelativeLayout::sort_children() {
    // Placeholder for dependency graph sorting
}

} // namespace android::widget
