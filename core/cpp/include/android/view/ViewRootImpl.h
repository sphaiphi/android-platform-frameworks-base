#pragma once

#include <android/view/View.h>
#include <android/view/IWindowSession.h>
#include <android/graphics/RenderNode.h>
#include <memory>

namespace android::view {

class ViewRootImpl {
public:
    ViewRootImpl();
    virtual ~ViewRootImpl() = default;

    void set_view(const std::shared_ptr<View>& view) { view_ = view; }
    auto get_view() const -> std::shared_ptr<View> { return view_; }

    void set_window_session(const std::shared_ptr<IWindowSession>& session) { window_session_ = session; }
    auto get_window_session() const -> std::shared_ptr<IWindowSession> { return window_session_; }

    void perform_traversals();

private:
    std::shared_ptr<View> view_;
    std::shared_ptr<IWindowSession> window_session_;
    std::unique_ptr<android::graphics::RenderNode> root_render_node_;

    void perform_measure();
    void perform_layout();
    void perform_draw();
};

} // namespace android::view
