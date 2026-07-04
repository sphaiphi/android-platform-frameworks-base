#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <any>
#include <android/view/MotionEvent.h>
#include <android/view/KeyEvent.h>
#include <android/view/LayoutParams.h>
#include <android/view/ViewTypes.h>
#include <android/view/ViewParentMixin.h>
#include <android/view/ViewManagerMixin.h>

namespace android::graphics {
class Canvas;
class Drawable;
}

namespace android::view {

class ViewPropertyAnimator;

class View : public std::enable_shared_from_this<View>,
             public ViewParentMixin<View>,
             public ViewManagerMixin<View> {
    // Grant CRTP mixins access to protected members.
    friend class ViewParentMixin<View>;
    friend class ViewManagerMixin<View>;

public:
    using Visibility = android::view::Visibility;
    static constexpr int32_t VISIBLE = 0;
    static constexpr int32_t INVISIBLE = 4;
    static constexpr int32_t GONE = 8;
    using MeasureSpec = android::view::MeasureSpec;
    static constexpr int32_t NO_ID = -1;

    View() = default;
    virtual ~View() = default;

    [[nodiscard]] auto get_id() const -> int32_t { return id_; }
    void set_id(int32_t id) { id_ = id; }

    [[nodiscard]] std::optional<std::any> get_tag() const { return tag_; }
    void set_tag(std::any tag) { tag_ = std::move(tag); }

    [[nodiscard]] Visibility get_visibility() const { return visibility_; }
    void set_visibility(Visibility visibility);

    [[nodiscard]] bool is_enabled() const { return has_flag(ViewFlags::ENABLED); }
    void set_enabled(bool enabled) {
        if (enabled) flags_ = static_cast<ViewFlags>(static_cast<uint32_t>(flags_) | static_cast<uint32_t>(ViewFlags::ENABLED));
        else flags_ = static_cast<ViewFlags>(static_cast<uint32_t>(flags_) & ~static_cast<uint32_t>(ViewFlags::ENABLED));
    }

    [[nodiscard]] bool is_focusable() const { return has_flag(ViewFlags::FOCUSABLE); }
    void set_focusable(bool f) {
        if (f) flags_ = static_cast<ViewFlags>(static_cast<uint32_t>(flags_) | static_cast<uint32_t>(ViewFlags::FOCUSABLE));
        else flags_ = static_cast<ViewFlags>(static_cast<uint32_t>(flags_) & ~static_cast<uint32_t>(ViewFlags::FOCUSABLE));
    }
    [[nodiscard]] bool is_clickable() const { return has_flag(ViewFlags::CLICKABLE); }
    void set_clickable(bool c) {
        if (c) flags_ = static_cast<ViewFlags>(static_cast<uint32_t>(flags_) | static_cast<uint32_t>(ViewFlags::CLICKABLE));
        else flags_ = static_cast<ViewFlags>(static_cast<uint32_t>(flags_) & ~static_cast<uint32_t>(ViewFlags::CLICKABLE));
    }

    [[nodiscard]] auto get_left() const -> int32_t { return left_; }
    [[nodiscard]] auto get_top() const -> int32_t { return top_; }
    [[nodiscard]] auto get_right() const -> int32_t { return right_; }
    [[nodiscard]] auto get_bottom() const -> int32_t { return bottom_; }
    [[nodiscard]] auto get_width() const -> int32_t { return right_ - left_; }
    [[nodiscard]] auto get_height() const -> int32_t { return bottom_ - top_; }

    void layout(int32_t l, int32_t t, int32_t r, int32_t b);
    [[nodiscard]] auto get_layout_params() const -> std::shared_ptr<LayoutParams> { return layout_params_; }
    void set_layout_params(const std::shared_ptr<LayoutParams>& p) { layout_params_ = p; }
    [[nodiscard]] View* get_parent() const { return parent_; }
    void set_parent(View* p) { parent_ = p; }

    [[nodiscard]] auto get_measured_width() const -> int32_t { return measured_width_; }
    [[nodiscard]] auto get_measured_height() const -> int32_t { return measured_height_; }
    [[nodiscard]] bool is_measured() const { return measured_; }
    void measure(int32_t w, int32_t h);

    void draw(android::graphics::Canvas& canvas);
    void set_background(std::shared_ptr<android::graphics::Drawable> bg);
    [[nodiscard]] std::shared_ptr<android::graphics::Drawable> get_background() const;

    [[nodiscard]] auto get_alpha() const -> float { return mAlpha_; }
    void set_alpha(float v) { mAlpha_ = (v < 0.0f) ? 0.0f : ((v > 1.0f) ? 1.0f : v); }
    [[nodiscard]] auto get_rotation() const -> float { return mRotation_; }
    void set_rotation(float v) { mRotation_ = v; }
    [[nodiscard]] auto get_rotation_x() const -> float { return mRotationX_; }
    void set_rotation_x(float v) { mRotationX_ = v; }
    [[nodiscard]] auto get_rotation_y() const -> float { return mRotationY_; }
    void set_rotation_y(float v) { mRotationY_ = v; }
    [[nodiscard]] auto get_rotation_z() const -> float { return mRotationZ_; }
    void set_rotation_z(float v) { mRotationZ_ = v; }
    [[nodiscard]] auto get_scale_x() const -> float { return mScaleX_; }
    void set_scale_x(float v) { mScaleX_ = v; }
    [[nodiscard]] auto get_scale_y() const -> float { return mScaleY_; }
    void set_scale_y(float v) { mScaleY_ = v; }
    [[nodiscard]] auto get_translation_x() const -> float { return mTranslationX_; }
    void set_translation_x(float v) { mTranslationX_ = v; }
    [[nodiscard]] auto get_translation_y() const -> float { return mTranslationY_; }
    void set_translation_y(float v) { mTranslationY_ = v; }
    [[nodiscard]] auto get_min_width() const -> int32_t { return minWidth_; }
    void set_min_width(int32_t v) { minWidth_ = v; }
    [[nodiscard]] auto get_min_height() const -> int32_t { return minHeight_; }
    void set_min_height(int32_t v) { minHeight_ = v; }

    [[nodiscard]] auto get_padding_left() const -> int32_t { return paddingLeft_; }
    [[nodiscard]] auto get_padding_top() const -> int32_t { return paddingTop_; }
    [[nodiscard]] auto get_padding_right() const -> int32_t { return paddingRight_; }
    [[nodiscard]] auto get_padding_bottom() const -> int32_t { return paddingBottom_; }
    void set_padding(int l, int t, int r, int b) { paddingLeft_=l; paddingTop_=t; paddingRight_=r; paddingBottom_=b; }
    [[nodiscard]] auto get_padding_start() const -> int32_t {
        return (layout_direction_ == LayoutDirection::Rtl) ? paddingRight_ : paddingLeft_; }
    [[nodiscard]] auto get_padding_end() const -> int32_t {
        return (layout_direction_ == LayoutDirection::Rtl) ? paddingLeft_ : paddingRight_; }
    [[nodiscard]] auto get_layout_direction() const -> LayoutDirection { return layout_direction_; }
    void set_layout_direction(LayoutDirection d) { layout_direction_ = d; }

    void request_layout();
    [[nodiscard]] bool is_layout_requested() const { return layoutRequested_; }
    void invalidate();

    [[nodiscard]] auto get_x() const -> float { return static_cast<float>(left_) + mTranslationX_; }
    [[nodiscard]] auto get_y() const -> float { return static_cast<float>(top_) + mTranslationY_; }

    auto animate() -> std::shared_ptr<ViewPropertyAnimator>;
    static auto resolve_size(int32_t s, int32_t m) -> int32_t;

    virtual bool dispatch_touch_event(const MotionEvent& event);
    bool dispatch_pointer_event(const MotionEvent& event);
    virtual bool dispatch_key_event(const KeyEvent& event);
    virtual bool on_touch_event(const MotionEvent& event);
    virtual bool on_key_event(const KeyEvent& event);

    [[nodiscard]] bool is_focused() const { return focused_; }
    virtual bool request_focus();
    virtual void clear_focus();

protected:
    // CRTP accessor: returns the parent View pointer for parent chain propagation.
    [[nodiscard]] virtual auto on_get_parent() const -> View* { return parent_; }

    virtual void on_layout(bool changed, int32_t l, int32_t t, int32_t r, int32_t b);
    virtual void on_measure(int32_t wms, int32_t hms);
    virtual void on_draw(android::graphics::Canvas& canvas);
    virtual void dispatch_draw(android::graphics::Canvas& canvas);
    void set_measured_dimension(int32_t mw, int32_t mh);
    [[nodiscard]] bool has_flag(ViewFlags f) const {
        return (static_cast<uint32_t>(flags_) & static_cast<uint32_t>(f)) != 0; }

    // Protected so CRTP mixins (ViewParentMixin<View>) can access directly.
    bool layoutRequested_{false};
    View* parent_{nullptr};

private:
    int32_t id_{NO_ID};
    std::optional<std::any> tag_;
    Visibility visibility_{Visibility::Visible};
    bool enabled_{true};
    ViewFlags flags_{ViewFlags::ENABLED};
    int32_t left_{0}, top_{0}, right_{0}, bottom_{0};
    int32_t measured_width_{0}, measured_height_{0};
    bool measured_{false}, focused_{false};
    float mTranslationX_{0.0f}, mTranslationY_{0.0f}, mAlpha_{1.0f};
    float mRotation_{0.0f}, mRotationX_{0.0f}, mRotationY_{0.0f}, mRotationZ_{0.0f};
    float mScaleX_{1.0f}, mScaleY_{1.0f};
    int32_t minWidth_{0}, minHeight_{0};
    int32_t paddingLeft_{0}, paddingTop_{0}, paddingRight_{0}, paddingBottom_{0};
    LayoutDirection layout_direction_{LayoutDirection::Ltr};
    std::shared_ptr<LayoutParams> layout_params_;
    std::shared_ptr<android::graphics::Drawable> background_;
};

} // namespace android::view
