#pragma once

#include <cstdint>
#include <android/view/ViewTypes.h>

namespace android::view {

class View;

// CRTP mixin for ViewParent interface.
// Pure CRTP: no explicit self/parent parameters. Casts `this` to Derived*
// and accesses derived-specific members (layoutRequested_, parent_, on_get_parent()).
//
// Derived class must provide:
//   - bool layoutRequested_ (protected, default false)
//   - View* parent_ (protected, default nullptr)
//   - View* on_get_parent() const (protected, returns parent or nullptr)
template <typename Derived>
class ViewParentMixin {
public:
    // Propagates layout request upward through the parent chain.
    void request_layout() {
        Derived* self = static_cast<Derived*>(this);
        self->layoutRequested_ = true;
        View* parent = self->on_get_parent();
        if (parent != nullptr) {
            // Get parent's mixin via ViewParentMixin<View> base
            ViewParentMixin<View>* parentMixin =
                static_cast<ViewParentMixin<View>*>(static_cast<void*>(parent));
            if (parentMixin != nullptr) {
                parentMixin->request_layout();
            }
        }
    }

    [[nodiscard]] bool is_layout_requested() const {
        const Derived* self = static_cast<const Derived*>(this);
        return self->layoutRequested_;
    }

    // Propagates invalidation upward through the parent chain.
    void on_descendant_invalidated(View* child, View* target) {
        const Derived* self = static_cast<const Derived*>(this);
        View* parent = self->on_get_parent();
        if (parent != nullptr) {
            ViewParentMixin<View>* parentMixin =
                static_cast<ViewParentMixin<View>*>(static_cast<void*>(parent));
            if (parentMixin != nullptr) {
                parentMixin->on_descendant_invalidated(child, target);
            }
        }
    }

    // Requests focus propagation upward.
    void request_child_focus(View* child, View* focused) {
        Derived* self = static_cast<Derived*>(this);
        View* parent = self->on_get_parent();
        if (parent != nullptr) {
            ViewParentMixin<View>* parentMixin =
                static_cast<ViewParentMixin<View>*>(static_cast<void*>(parent));
            if (parentMixin != nullptr) {
                parentMixin->request_child_focus(child, focused);
            }
        }
    }

    // Clears focus propagation upward.
    void clear_child_focus(View* child) {
        Derived* self = static_cast<Derived*>(this);
        View* parent = self->on_get_parent();
        if (parent != nullptr) {
            ViewParentMixin<View>* parentMixin =
                static_cast<ViewParentMixin<View>*>(static_cast<void*>(parent));
            if (parentMixin != nullptr) {
                parentMixin->clear_child_focus(child);
            }
        }
    }

    // Focus search stub — returns nullptr per plan open question.
    [[nodiscard]] View* focus_search(View* v, int direction) {
        (void)v; (void)direction;
        return nullptr;
    }
};

} // namespace android::view
