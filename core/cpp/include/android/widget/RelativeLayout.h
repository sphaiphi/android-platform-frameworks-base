#pragma once

#include <android/view/ViewGroup.h>
#include <map>

namespace android::widget {

class RelativeLayout : public android::view::ViewGroup<android::view::MarginLayoutParams> {
public:
    enum Rule {
        LEFT_OF = 0,
        RIGHT_OF = 1,
        ABOVE = 2,
        BELOW = 3,
        ALIGN_BASELINE = 4,
        ALIGN_LEFT = 5,
        ALIGN_TOP = 6,
        ALIGN_RIGHT = 7,
        ALIGN_BOTTOM = 8,
        ALIGN_PARENT_LEFT = 9,
        ALIGN_PARENT_TOP = 10,
        ALIGN_PARENT_RIGHT = 11,
        ALIGN_PARENT_BOTTOM = 12,
        CENTER_IN_PARENT = 13,
        CENTER_HORIZONTAL = 14,
        CENTER_VERTICAL = 15,
        START_OF = 16,
        END_OF = 17,
        ALIGN_START = 18,
        ALIGN_END = 19,
        ALIGN_PARENT_START = 20,
        ALIGN_PARENT_END = 21,
        RULE_COUNT = 22
    };

    static constexpr int32_t TRUE = -1;

    class LayoutParams : public android::view::MarginLayoutParams {
    public:
        LayoutParams(int32_t w, int32_t h) : MarginLayoutParams(w, h) {
            for (int i = 0; i < RULE_COUNT; ++i) rules[i] = 0;
        }

        void add_rule(int32_t verb) { rules[verb] = TRUE; }
        void add_rule(int32_t verb, int32_t anchor) { rules[verb] = anchor; }
        void remove_rule(int32_t verb) { rules[verb] = 0; }
        auto get_rule(int32_t verb) const -> int32_t { return rules[verb]; }

        int32_t rules[RULE_COUNT];
        
        // Internal state used during layout
        int32_t min_left, min_top, max_right, max_bottom;
    };

    RelativeLayout() = default;
    virtual ~RelativeLayout() = default;

protected:
    void on_measure(int32_t width_measure_spec, int32_t height_measure_spec) override;
    void on_layout(bool changed, int32_t left, int32_t top, int32_t right, int32_t bottom) override;

    auto generate_default_layout_params() -> std::shared_ptr<android::view::LayoutParams> override {
        return std::make_shared<LayoutParams>(android::view::LayoutParams::WRAP_CONTENT, android::view::LayoutParams::WRAP_CONTENT);
    }

private:
    struct DependencyGraph {
        struct Node {
            std::shared_ptr<android::view::View> view;
            std::vector<int32_t> dependents;
            std::map<int32_t, Node*> dependencies;
        };
        std::vector<Node*> sorted_nodes;
    };

    void sort_children();
};

} // namespace android::widget
