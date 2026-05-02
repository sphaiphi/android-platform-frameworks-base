#pragma once

#include <cstdint>
#include <memory>
#include <android/view/MotionEvent.h>
#include <android/view/KeyEvent.h>
#include <android/view/LayoutParams.h>

namespace android::graphics {
class Canvas;
class Drawable;
}

namespace android::view {

class View {
public:
    enum Visibility {
        VISIBLE = 0x00000000,
        INVISIBLE = 0x00000004,
        GONE = 0x00000008
    };

    static constexpr int32_t NO_ID = -1;

    class MeasureSpec {
    public:
        static constexpr uint32_t MODE_SHIFT = 30;
        static constexpr uint32_t MODE_MASK  = 0x3 << MODE_SHIFT;
        
        static constexpr uint32_t UNSPECIFIED = 0 << MODE_SHIFT;
        static constexpr uint32_t EXACTLY     = 1 << MODE_SHIFT;
        static constexpr uint32_t AT_MOST     = 2 << MODE_SHIFT;

        static auto make_measure_spec(uint32_t size, uint32_t mode) -> uint32_t {
            return (size & ~MODE_MASK) | (mode & MODE_MASK);
        }

        static auto get_mode(uint32_t measure_spec) -> uint32_t {
            return measure_spec & MODE_MASK;
        }

        static auto get_size(uint32_t measure_spec) -> uint32_t {
            return measure_spec & ~MODE_MASK;
        }
    };

    View() = default;
    virtual ~View() = default;

    auto get_visibility() const -> Visibility { return visibility_; }
    void set_visibility(Visibility visibility) { visibility_ = visibility; }

    auto get_id() const -> int32_t { return id_; }
    void set_id(int32_t id) { id_ = id; }

    auto is_enabled() const -> bool { return enabled_; }
    void set_enabled(bool enabled) { enabled_ = enabled; }

    // Coordinate system
    auto get_left() const -> int32_t { return left_; }
    auto get_top() const -> int32_t { return top_; }
    auto get_right() const -> int32_t { return right_; }
    auto get_bottom() const -> int32_t { return bottom_; }
    auto get_width() const -> int32_t { return right_ - left_; }
    auto get_height() const -> int32_t { return bottom_ - top_; }

    void layout(int32_t l, int32_t t, int32_t r, int32_t b);

    // Layout params
    auto get_layout_params() const -> std::shared_ptr<LayoutParams> { return layout_params_; }
    void set_layout_params(const std::shared_ptr<LayoutParams>& params) { layout_params_ = params; }

    // Parent management
    auto get_parent() const -> View* { return parent_; }
    void set_parent(View* parent) { parent_ = parent; }

    // Measurement
    auto get_measured_width() const -> int32_t { return measured_width_; }
    auto get_measured_height() const -> int32_t { return measured_height_; }

    void measure(int32_t width_measure_spec, int32_t height_measure_spec);

    void draw(android::graphics::Canvas& canvas);

    // Background
    void set_background(std::shared_ptr<android::graphics::Drawable> bg);
    [[nodiscard]] std::shared_ptr<android::graphics::Drawable> get_background() const;

    static auto resolve_size(int32_t size, int32_t measure_spec) -> int32_t;

    // Input Events
    virtual bool dispatch_touch_event(const MotionEvent& event);
    virtual bool dispatch_key_event(const KeyEvent& event);

    virtual bool on_touch_event(const MotionEvent& event);
    virtual bool on_key_event(const KeyEvent& event);

    // Focus
    bool is_focused() const { return focused_; }
    bool is_focusable() const { return focusable_; }
    void set_focusable(bool focusable) { focusable_ = focusable; }
    virtual bool request_focus();
    virtual void clear_focus();

protected:
    virtual void on_layout(bool changed, int32_t left, int32_t top, int32_t right, int32_t bottom);
    virtual void on_measure(int32_t width_measure_spec, int32_t height_measure_spec);
    virtual void on_draw(android::graphics::Canvas& canvas);
    virtual void dispatch_draw(android::graphics::Canvas& canvas);

    void set_measured_dimension(int32_t measured_width, int32_t measured_height);

private:
    Visibility visibility_{VISIBLE};
    int32_t id_{NO_ID};
    bool enabled_{true};

    int32_t left_{0};
    int32_t top_{0};
    int32_t right_{0};
    int32_t bottom_{0};

    View* parent_{nullptr};

    int32_t measured_width_{0};
    int32_t measured_height_{0};

    bool focused_{false};
    bool focusable_{false};

    std::shared_ptr<LayoutParams> layout_params_;
    std::shared_ptr<android::graphics::Drawable> background_;
};

} // namespace android::view
