#pragma once

#include <android/view/View.h>
#include <android/view/Interpolator.h>

#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace android::view {

/**
 * ViewPropertyAnimator — fluent, optimized animation API for View properties.
 *
 * Animates select properties (alpha, translationX/Y, rotation, scaleX/Y) on a
 * View using a Choreographer-driven frame loop. Multiple property changes are
 * batched into a single animation, producing one invalidation per frame.
 *
 * Usage:
 *   view->animate()
 *       ->alpha(0.5f)
 *       ->rotation(45.0f)
 *       ->set_duration(300)
 *       ->start();
 *
 * Thread safety: The VPA is tied to the View's thread (typically the UI thread).
 * All methods must be called on the same thread as the View.
 *
 * Lifetime: The VPA is managed via shared_ptr. The Choreographer callback holds
 * a weak_ptr to the VPA, so if the VPA is destroyed, the callback is a no-op.
 */
class ViewPropertyAnimator : public std::enable_shared_from_this<ViewPropertyAnimator> {
public:
    /**
     * Property type constants for internal tracking.
     */
    enum Property : int {
        TRANSLATION_X = 0x01,
        TRANSLATION_Y = 0x02,
        ALPHA         = 0x04,
        ROTATION      = 0x08,
        SCALE_X       = 0x10,
        SCALE_Y       = 0x20,
        ALL = TRANSLATION_X | TRANSLATION_Y | ALPHA | ROTATION | SCALE_X | SCALE_Y
    };

    /**
     * Fluent property methods — animate to absolute value.
     * Each call queues a pending animation target.
     */
    auto alpha(float value) -> ViewPropertyAnimator&;
    auto alpha_by(float delta) -> ViewPropertyAnimator&;
    auto translation_x(float value) -> ViewPropertyAnimator&;
    auto translation_x_by(float delta) -> ViewPropertyAnimator&;
    auto translation_y(float value) -> ViewPropertyAnimator&;
    auto translation_y_by(float delta) -> ViewPropertyAnimator&;
    auto rotation(float value) -> ViewPropertyAnimator&;
    auto rotation_by(float delta) -> ViewPropertyAnimator&;
    auto scale_x(float value) -> ViewPropertyAnimator&;
    auto scale_x_by(float delta) -> ViewPropertyAnimator&;
    auto scale_y(float value) -> ViewPropertyAnimator&;
    auto scale_y_by(float delta) -> ViewPropertyAnimator&;
    auto x(float value) -> ViewPropertyAnimator&;       // visual X = left + translationX
    auto x_by(float delta) -> ViewPropertyAnimator&;
    auto y(float value) -> ViewPropertyAnimator&;       // visual Y = top + translationY
    auto y_by(float delta) -> ViewPropertyAnimator&;

    /**
     * Configuration methods.
     */
    auto set_duration(int64_t ms) -> ViewPropertyAnimator&;
    auto set_start_delay(int64_t ms) -> ViewPropertyAnimator&;
    auto set_interpolator(std::shared_ptr<Interpolator> interpolator) -> ViewPropertyAnimator&;
    auto with_start_action(std::function<void()> action) -> ViewPropertyAnimator&;
    auto with_end_action(std::function<void()> action) -> ViewPropertyAnimator&;

    /**
     * Lifecycle methods.
     */
    void start();
    void cancel();

    /**
     * Query methods.
     */
    [[nodiscard]] auto is_running() const -> bool;
    [[nodiscard]] auto is_pending() const -> bool;
    [[nodiscard]] auto get_duration() const -> int64_t;

    /**
     * Get the associated View (for the Choreographer callback).
     */
    [[nodiscard]] auto get_view() const -> std::shared_ptr<View>;

#ifdef HOST_BUILD
    /**
     * Test helper: advance the animation's perceived time by the given milliseconds.
     * This allows tests to simulate time passing without needing a real Looper.
     */
    void test_advance_time(int64_t ms);
#endif

private:
    // Internal data holder for a pending property animation.
    struct NameValuesHolder {
        Property property;
        float value;       // target value (or delta for _by methods)
        bool is_delta;     // true if value is a delta, false if absolute
    };

    // The View being animated (set when VPA is created via View::animate()).
    std::weak_ptr<View> m_view_;

    // Pending animation queue — properties queued before start().
    std::vector<NameValuesHolder> m_pending_;

    // Configuration.
    int64_t m_duration_ms_ = 300;
    int64_t m_start_delay_ms_ = 0;
    std::shared_ptr<Interpolator> m_interpolator_;

    // Lifecycle callbacks.
    std::function<void()> m_start_action_;
    std::function<void()> m_end_action_;

    // Animation state.
    enum class State { PENDING, RUNNING, CANCELED };
    State m_state_ = State::PENDING;

    // Animation timing (nanoseconds from Choreographer::system_time_nanos).
    int64_t m_start_time_nanos_ = 0;

    // Constructor — only accessible via View::animate().
    explicit ViewPropertyAnimator(std::shared_ptr<View> view);

    // The Choreographer frame callback (posted when start() is called).
    void on_frame(int64_t frame_time_nanos);

    // Apply interpolated values to the View.
    void apply_pending_values();

    // Friend: only View can create VPA instances.
    friend class View;
};

} // namespace android::view
