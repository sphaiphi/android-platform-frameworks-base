#pragma once

namespace android::view {

class Window {
public:
    Window() = default;
    virtual ~Window() = default;

    virtual void set_content_view(int layout_res_id) = 0;
};

} // namespace android::view
