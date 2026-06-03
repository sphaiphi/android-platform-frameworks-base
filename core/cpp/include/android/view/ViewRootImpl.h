#pragma once

#include <android/view/View.h>
#include <android/view/IWindowSession.h>
#include <android/graphics/RenderNode.h>
#include <android/view/MotionEvent.h>
#include <memory>

namespace android::view {

class Choreographer;

class ViewRootImpl : public std::enable_shared_from_this<ViewRootImpl> {
public:
    ViewRootImpl();
    virtual ~ViewRootImpl() = default;

    void set_view(const std::shared_ptr<View>& view);
    void remove_view();
    auto get_view() const -> std::shared_ptr<View> { return view_; }

    void set_window(const std::shared_ptr<IWindow>& window) { window_ = window; }
    auto get_window() const -> std::shared_ptr<IWindow> { return window_; }

    void set_window_session(const std::shared_ptr<IWindowSession>& session) { window_session_ = session; }
    auto get_window_session() const -> std::shared_ptr<IWindowSession> { return window_session_; }

    // Choreographer integration
    void set_choreographer(std::weak_ptr<Choreographer> choreographer);
    void remove_choreographer();

    void perform_traversals();
    bool dispatch_pointer_event(const MotionEvent& event);

private:
    std::shared_ptr<View> view_;
    std::shared_ptr<IWindow> window_;
    std::shared_ptr<IWindowSession> window_session_;
    std::unique_ptr<android::graphics::RenderNode> root_render_node_;

    // Choreographer integration
    std::weak_ptr<Choreographer> m_choreographer_;
    bool m_choreographer_set_ = false;

    void perform_measure();
    void perform_layout();
    void perform_draw();
};

} // namespace android::view
