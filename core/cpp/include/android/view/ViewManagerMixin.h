#pragma once

#include <memory>
#include <android/view/View.h>
#include <android/view/LayoutParams.h>

namespace android::view {

// CRTP mixin providing the ViewManager interface with zero-cost static dispatch.
// Derived must implement:
//   - void add_view(std::shared_ptr<View>, std::shared_ptr<LayoutParams>)
//   - void update_view_layout(std::shared_ptr<View>, std::shared_ptr<LayoutParams>)
//   - void remove_view(std::shared_ptr<View>)
template <typename Derived>
class ViewManagerMixin {
public:
    void add_view(std::shared_ptr<View> view, std::shared_ptr<LayoutParams> params) {
        static_cast<Derived*>(this)->add_view(std::move(view), std::move(params));
    }

    void update_view_layout(std::shared_ptr<View> view, std::shared_ptr<LayoutParams> params) {
        static_cast<Derived*>(this)->update_view_layout(std::move(view), std::move(params));
    }

    void remove_view(std::shared_ptr<View> view) {
        static_cast<Derived*>(this)->remove_view(std::move(view));
    }
};

} // namespace android::view
