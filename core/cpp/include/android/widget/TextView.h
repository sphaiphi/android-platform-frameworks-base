#pragma once

#include <android/view/View.h>
#include <string>

namespace android::widget {

class TextView : public android::view::View {
public:
    TextView() = default;
    virtual ~TextView() = default;

    auto get_text() const -> std::string { return text_; }
    void set_text(const std::string& text) { 
        text_ = text;
        // In a real TextView, this would trigger request_layout and invalidate
    }

protected:
    void on_measure(int32_t width_measure_spec, int32_t height_measure_spec) override;
    void on_draw(android::graphics::Canvas& canvas) override;

private:
    std::string text_;
};

} // namespace android::widget
