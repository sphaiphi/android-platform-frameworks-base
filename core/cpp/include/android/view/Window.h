#pragma once

#include <memory>

namespace android::view {

class View;

class Window {
public:
    class Callback {
    public:
        virtual ~Callback() = default;
        virtual void on_content_changed() = 0;
        virtual bool dispatch_key_event(int keycode) = 0;
        virtual bool dispatch_touch_event(int action, float x, float y) = 0;
    };

    Window() = default;
    virtual ~Window() = default;

    virtual void set_content_view(int layout_res_id) = 0;
    virtual void set_content_view(const std::shared_ptr<View>& view) = 0;

    void set_callback(const std::shared_ptr<Callback>& callback) { callback_ = callback; }
    auto get_callback() const -> std::shared_ptr<Callback> { return callback_; }

private:
    std::shared_ptr<Callback> callback_;
};

} // namespace android::view
