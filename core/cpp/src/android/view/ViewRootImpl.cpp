#include <android/view/ViewRootImpl.h>
#include <android/graphics/Canvas.h>
#include <android/graphics/RenderNode.h>
#include <android/view/InputChannel.h>
#include <android/view/InsetsState.h>
#include <android/view/InsetsSourceControlArray.h>
#include <android/view/WindowRelayoutResult.h>

namespace android::view {

#ifdef HOST_BUILD
class HostCanvas : public android::graphics::Canvas {
public:
    HostCanvas() : android::graphics::Canvas(1, 1) {}
    void draw_rect(int32_t /*l*/, int32_t /*t*/, int32_t /*r*/, int32_t /*b*/) override {}
};

class HostRenderNode : public android::graphics::RenderNode {
public:
    using android::graphics::RenderNode::RenderNode;
    android::graphics::Canvas* begin_recording(int32_t /*width*/, int32_t /*height*/) override {
        return &canvas_;
    }
    void end_recording() override {}
    bool has_display_list() const override { return true; }
private:
    HostCanvas canvas_;
};
#endif

ViewRootImpl::ViewRootImpl() {
#ifdef HOST_BUILD
    root_render_node_ = std::make_unique<HostRenderNode>("ViewRootImpl");
#endif
}

void ViewRootImpl::perform_traversals() {
    if (!view_) return;

    if (window_session_) {
        std::shared_ptr<InputChannel> out_input_channel;
        std::shared_ptr<InsetsState> out_insets_state;
        std::shared_ptr<InsetsSourceControlArray> out_active_controls;
        android::graphics::Rect out_attached_frame;
        std::vector<float> out_size_compat_scale;

        window_session_->add_to_display(
            window_, nullptr, 0, 0, 0,
            out_input_channel, out_insets_state, out_active_controls,
            out_attached_frame, out_size_compat_scale);

        std::shared_ptr<WindowRelayoutResult> out_result;
        window_session_->relayout(
            window_, nullptr,
            view_->get_measured_width(), view_->get_measured_height(),
            0, 0, 1, 0, out_result);
    }

    perform_measure();
    perform_layout();
    perform_draw();
}

void ViewRootImpl::perform_measure() {
    if (!view_) return;

    // Default to EXACTLY with some reasonable size for now, 
    // or use previous window size if available.
    int32_t width_spec = View::MeasureSpec::make_measure_spec(1080, View::MeasureSpec::EXACTLY);
    int32_t height_spec = View::MeasureSpec::make_measure_spec(1920, View::MeasureSpec::EXACTLY);
    
    view_->measure(width_spec, height_spec);
}

void ViewRootImpl::perform_layout() {
    if (!view_) return;

    view_->layout(0, 0, view_->get_measured_width(), view_->get_measured_height());
}

void ViewRootImpl::perform_draw() {
    if (!view_) return;
    if (!root_render_node_) return;

    auto canvas = root_render_node_->begin_recording(view_->get_width(), view_->get_height());
    if (canvas) {
        view_->draw(*canvas);
        root_render_node_->end_recording();
    }
}

bool ViewRootImpl::dispatch_pointer_event(const MotionEvent& event) {
    if (!view_) return false;
    return view_->dispatch_pointer_event(event);
}

} // namespace android::view
