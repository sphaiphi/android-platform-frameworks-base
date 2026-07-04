#include <android/widget/LinearLayout.h>
#include <android/view/Gravity.h>
#include <algorithm>

namespace android::widget {

using namespace android::view;

void LinearLayout::on_measure(int32_t width_measure_spec, int32_t height_measure_spec) {
    if (orientation_ == VERTICAL) {
        measure_vertical(width_measure_spec, height_measure_spec);
    } else {
        measure_horizontal(width_measure_spec, height_measure_spec);
    }
}

void LinearLayout::measure_vertical(int32_t width_measure_spec, int32_t height_measure_spec) {
    int32_t total_height = 0;
    int32_t max_width = 0;
    float total_weight = 0.0f;
    
    // First pass: measure children without weights and sum weights
    for (int i = 0; i < get_child_count(); ++i) {
        auto child = this->get_child_at(i);
        if (child && child->get_visibility() != Visibility::Gone) {
            auto lp = child->get_layout_params();
            auto llp = std::dynamic_pointer_cast<LayoutParams>(lp);
            
            float weight = llp ? llp->weight : 0.0f;
            total_weight += weight;
            
            if (weight > 0 && lp->height == 0) {
                // Skip for now, will be measured in second pass
                // But we still need to calculate max_width if child is match_parent
                int32_t child_width_spec = get_child_measure_spec(width_measure_spec, 0, lp->width);
                child->measure(child_width_spec, MeasureSpec::make(0, MeasureSpec::UNSPECIFIED));
                max_width = std::max(max_width, child->get_measured_width());
            } else {
                int32_t child_width_spec = get_child_measure_spec(width_measure_spec, 0, lp->width);
                int32_t child_height_spec = get_child_measure_spec(height_measure_spec, total_height, lp->height);
                child->measure(child_width_spec, child_height_spec);
                total_height += child->get_measured_height();
                max_width = std::max(max_width, child->get_measured_width());
            }
        }
    }
    
    // Second pass: distribute remaining space based on weights
    if (total_weight > 0) {
        int32_t height_size = MeasureSpec::get_size(height_measure_spec);
        int32_t remaining_height = std::max(0, height_size - total_height);
        float weight_sum = total_weight;
        
        for (int i = 0; i < get_child_count(); ++i) {
            auto child = this->get_child_at(i);
            if (child && child->get_visibility() != Visibility::Gone) {
                auto lp = child->get_layout_params();
                auto llp = std::dynamic_pointer_cast<LayoutParams>(lp);
                float weight = llp ? llp->weight : 0.0f;

                if (weight > 0) {
                    int32_t share = static_cast<int32_t>(remaining_height * weight / weight_sum);
                    remaining_height -= share;
                    weight_sum -= weight;

                    int32_t child_height = (lp->height == 0) ? share : child->get_measured_height() + share;
                    
                    int32_t child_width_spec = get_child_measure_spec(width_measure_spec, 0, lp->width);
                    int32_t child_height_spec = MeasureSpec::make(child_height, MeasureSpec::EXACTLY);
                    child->measure(child_width_spec, child_height_spec);
                    
                    max_width = std::max(max_width, child->get_measured_width());
                }
            }
        }
        total_height = height_size; // Force to spec size for weight distribution
    }
    
    set_measured_dimension(
        View::resolve_size(max_width, width_measure_spec),
        View::resolve_size(total_height, height_measure_spec)
    );
}

void LinearLayout::measure_horizontal(int32_t width_measure_spec, int32_t height_measure_spec) {
    int32_t total_width = 0;
    int32_t max_height = 0;
    
    for (int i = 0; i < get_child_count(); ++i) {
        auto child = this->get_child_at(i);
        if (child && child->get_visibility() != Visibility::Gone) {
            auto lp = child->get_layout_params();
            int32_t child_width_spec = get_child_measure_spec(width_measure_spec, total_width, lp->width);
            int32_t child_height_spec = get_child_measure_spec(height_measure_spec, 0, lp->height);
            
            child->measure(child_width_spec, child_height_spec);
            
            total_width += child->get_measured_width();
            max_height = std::max(max_height, child->get_measured_height());
        }
    }
    
    set_measured_dimension(total_width, max_height);
}

void LinearLayout::on_layout(bool changed, int32_t left, int32_t top, int32_t right, int32_t bottom) {
    if (orientation_ == VERTICAL) {
        layout_vertical(left, top, right, bottom);
    } else {
        layout_horizontal(left, top, right, bottom);
    }
}

void LinearLayout::layout_vertical(int32_t left, int32_t top, int32_t right, int32_t bottom) {
    int32_t parent_width = right - left;
    int32_t parent_height = bottom - top;
    int32_t child_top = 0;

    int32_t total_child_height = 0;
    for (int i = 0; i < get_child_count(); ++i) {
        auto child = this->get_child_at(i);
        if (child && child->get_visibility() != Visibility::Gone) {
            total_child_height += child->get_measured_height();
        }
    }

    switch (gravity_ & Gravity::VERTICAL_GRAVITY_MASK) {
        case Gravity::CENTER_VERTICAL:
            child_top = (parent_height - total_child_height) / 2;
            break;
        case Gravity::BOTTOM:
            child_top = parent_height - total_child_height;
            break;
        case Gravity::TOP:
        default:
            child_top = 0;
            break;
    }
    
    for (int i = 0; i < get_child_count(); ++i) {
        auto child = this->get_child_at(i);
        if (child && child->get_visibility() != Visibility::Gone) {
            int32_t child_width = child->get_measured_width();
            int32_t child_height = child->get_measured_height();
            
            int32_t child_left = 0;
            auto lp = std::dynamic_pointer_cast<LayoutParams>(child->get_layout_params());
            int32_t gravity = (lp && lp->gravity != -1) ? lp->gravity : gravity_;

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

            child->layout(child_left, child_top, child_left + child_width, child_top + child_height);
            child_top += child_height;
        }
    }
}

void LinearLayout::layout_horizontal(int32_t left, int32_t top, int32_t right, int32_t bottom) {
    int32_t parent_width = right - left;
    int32_t parent_height = bottom - top;
    int32_t child_left = 0;

    int32_t total_child_width = 0;
    for (int i = 0; i < get_child_count(); ++i) {
        auto child = this->get_child_at(i);
        if (child && child->get_visibility() != Visibility::Gone) {
            total_child_width += child->get_measured_width();
        }
    }

    switch (gravity_ & Gravity::HORIZONTAL_GRAVITY_MASK) {
        case Gravity::CENTER_HORIZONTAL:
            child_left = (parent_width - total_child_width) / 2;
            break;
        case Gravity::RIGHT:
            child_left = parent_width - total_child_width;
            break;
        case Gravity::LEFT:
        default:
            child_left = 0;
            break;
    }
    
    for (int i = 0; i < get_child_count(); ++i) {
        auto child = this->get_child_at(i);
        if (child && child->get_visibility() != Visibility::Gone) {
            int32_t child_width = child->get_measured_width();
            int32_t child_height = child->get_measured_height();
            
            int32_t child_top = 0;
            auto lp = std::dynamic_pointer_cast<LayoutParams>(child->get_layout_params());
            int32_t gravity = (lp && lp->gravity != -1) ? lp->gravity : gravity_;

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
            child_left += child_width;
        }
    }
}

} // namespace android::widget
