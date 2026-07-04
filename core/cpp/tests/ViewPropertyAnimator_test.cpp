#include <gtest/gtest.h>
#include <android/view/View.h>
#include <android/view/ViewPropertyAnimator.h>
#include <android/view/Interpolator.h>
#include <android/view/Choreographer.h>
#include <android/os/Looper.h>

#include <gtest/gtest.h>

#include <atomic>
#include <memory>

using namespace android::view;
using namespace android::os;

// ============================================================================
// Helper: prepare a Looper on the current thread
// ============================================================================

static auto prepare_looper() -> std::shared_ptr<Looper> {
    Looper::prepare();
    return Looper::my_looper();
}

// ============================================================================
// Fluent API tests
// ============================================================================

TEST(ViewPropertyAnimatorTest, FluentChainingReturnsSelf) {
    auto view = std::make_shared<View>();
    view->layout(0, 0, 100, 100);
    auto vpa = view->animate();
    ASSERT_NE(vpa, nullptr);

    // Chained calls should return the same instance
    auto& result = vpa->alpha(0.5f);
    EXPECT_EQ(&result, vpa.get());

    auto& result2 = result.rotation(45.0f);
    EXPECT_EQ(&result2, vpa.get());
}

TEST(ViewPropertyAnimatorTest, MultiplePropertiesQueue) {
    auto view = std::make_shared<View>();
    view->layout(0, 0, 100, 100);
    auto vpa = view->animate();
    ASSERT_NE(vpa, nullptr);

    // Queue multiple properties
    vpa->alpha(0.5f).rotation(45.0f).scale_x(2.0f);

    // Verify state is pending
    EXPECT_TRUE(vpa->is_pending());
    EXPECT_FALSE(vpa->is_running());
}

TEST(ViewPropertyAnimatorTest, CancelStopsPending) {
    auto view = std::make_shared<View>();
    view->layout(0, 0, 100, 100);
    auto vpa = view->animate();
    ASSERT_NE(vpa, nullptr);

    vpa->alpha(0.5f);
    vpa->cancel();

    EXPECT_FALSE(vpa->is_pending());
    EXPECT_FALSE(vpa->is_running());
}

TEST(ViewPropertyAnimatorTest, NegativeDurationThrows) {
    auto view = std::make_shared<View>();
    view->layout(0, 0, 100, 100);
    auto vpa = view->animate();
    ASSERT_NE(vpa, nullptr);

    EXPECT_THROW(vpa->set_duration(-1), std::invalid_argument);
}

TEST(ViewPropertyAnimatorTest, ZeroDurationIsValid) {
    auto view = std::make_shared<View>();
    view->layout(0, 0, 100, 100);
    auto vpa = view->animate();
    ASSERT_NE(vpa, nullptr);

    EXPECT_NO_THROW(vpa->set_duration(0));
    EXPECT_EQ(0, vpa->get_duration());
}

TEST(ViewPropertyAnimatorTest, DefaultDuration) {
    auto view = std::make_shared<View>();
    view->layout(0, 0, 100, 100);
    auto vpa = view->animate();
    ASSERT_NE(vpa, nullptr);

    EXPECT_EQ(300, vpa->get_duration());
}

TEST(ViewPropertyAnimatorTest, SetDuration) {
    auto view = std::make_shared<View>();
    view->layout(0, 0, 100, 100);
    auto vpa = view->animate();
    ASSERT_NE(vpa, nullptr);

    vpa->set_duration(500);
    EXPECT_EQ(500, vpa->get_duration());
}

// ============================================================================
// _By method tests
// ============================================================================

TEST(ViewPropertyAnimatorTest, AlphaByQueuesDelta) {
    auto view = std::make_shared<View>();
    view->layout(0, 0, 100, 100);
    view->set_alpha(1.0f);
    auto vpa = view->animate();
    ASSERT_NE(vpa, nullptr);

    vpa->alpha_by(-0.5f);
    EXPECT_TRUE(vpa->is_pending());
}

TEST(ViewPropertyAnimatorTest, TranslationXByQueuesDelta) {
    auto view = std::make_shared<View>();
    view->layout(0, 0, 100, 100);
    auto vpa = view->animate();
    ASSERT_NE(vpa, nullptr);

    vpa->translation_x_by(50.0f);
    EXPECT_TRUE(vpa->is_pending());
}

TEST(ViewPropertyAnimatorTest, RotationByQueuesDelta) {
    auto view = std::make_shared<View>();
    view->layout(0, 0, 100, 100);
    auto vpa = view->animate();
    ASSERT_NE(vpa, nullptr);

    vpa->rotation_by(90.0f);
    EXPECT_TRUE(vpa->is_pending());
}

// ============================================================================
// Choreographer integration tests
// ============================================================================

TEST(ViewPropertyAnimatorTest, ChoreographerUpdatesAlpha) {
    auto looper = prepare_looper();
    ASSERT_NE(looper, nullptr);

    auto view = std::make_shared<View>();
    view->layout(0, 0, 100, 100);
    view->set_alpha(1.0f);

    auto vpa = view->animate();
    ASSERT_NE(vpa, nullptr);

    vpa->set_duration(100);
    vpa->alpha(0.5f);
    vpa->start();

    // Verify animation is running
    EXPECT_TRUE(vpa->is_running());

    // Simulate 50ms of time passing (half of 100ms duration)
    vpa->test_advance_time(50);

    // Trigger Choreographer frame
    auto choreo = Choreographer::get_instance();
    choreo->do_frame(Choreographer::system_time_nanos());

    // After 50% of duration, alpha should be between 1.0f and 0.5f
    float alpha = view->get_alpha();
    EXPECT_LT(alpha, 1.0f);
    EXPECT_GT(alpha, 0.5f);
}

TEST(ViewPropertyAnimatorTest, ChoreographerUpdatesTranslation) {
    auto looper = prepare_looper();
    ASSERT_NE(looper, nullptr);

    auto view = std::make_shared<View>();
    view->layout(0, 0, 100, 100);
    view->set_translation_x(0.0f);

    auto vpa = view->animate();
    ASSERT_NE(vpa, nullptr);

    vpa->set_duration(0);  // instant
    vpa->translation_x(50.0f);
    vpa->start();

    auto choreo = Choreographer::get_instance();
    choreo->do_frame(Choreographer::system_time_nanos());

    EXPECT_FLOAT_EQ(50.0f, view->get_translation_x());
}

TEST(ViewPropertyAnimatorTest, ChoreographerUpdatesRotation) {
    auto looper = prepare_looper();
    ASSERT_NE(looper, nullptr);

    auto view = std::make_shared<View>();
    view->layout(0, 0, 100, 100);
    view->set_rotation(0.0f);

    auto vpa = view->animate();
    ASSERT_NE(vpa, nullptr);

    vpa->set_duration(0);  // instant
    vpa->rotation(90.0f);
    vpa->start();

    auto choreo = Choreographer::get_instance();
    choreo->do_frame(Choreographer::system_time_nanos());

    EXPECT_FLOAT_EQ(90.0f, view->get_rotation());
}

TEST(ViewPropertyAnimatorTest, ChoreographerUpdatesScale) {
    auto looper = prepare_looper();
    ASSERT_NE(looper, nullptr);

    auto view = std::make_shared<View>();
    view->layout(0, 0, 100, 100);
    view->set_scale_x(1.0f);
    view->set_scale_y(1.0f);

    auto vpa = view->animate();
    ASSERT_NE(vpa, nullptr);

    vpa->set_duration(0);  // instant
    vpa->scale_x(2.0f).scale_y(0.5f);
    vpa->start();

    auto choreo = Choreographer::get_instance();
    choreo->do_frame(Choreographer::system_time_nanos());

    EXPECT_FLOAT_EQ(2.0f, view->get_scale_x());
    EXPECT_FLOAT_EQ(0.5f, view->get_scale_y());
}

TEST(ViewPropertyAnimatorTest, MultiplePropertiesAnimateTogether) {
    auto looper = prepare_looper();
    auto view = std::make_shared<View>();
    view->layout(0, 0, 100, 100);
    view->set_alpha(1.0f);
    view->set_translation_x(0.0f);
    view->set_rotation(0.0f);

    auto vpa = view->animate();
    vpa->set_duration(0);  // instant for predictable testing
    vpa->alpha(0.5f).translation_x(50.0f).rotation(90.0f);
    vpa->start();

    auto choreo = Choreographer::get_instance();
    choreo->do_frame(Choreographer::system_time_nanos());

    EXPECT_FLOAT_EQ(0.5f, view->get_alpha());
    EXPECT_FLOAT_EQ(50.0f, view->get_translation_x());
    EXPECT_FLOAT_EQ(90.0f, view->get_rotation());
}

// ============================================================================
// Interpolator tests
// ============================================================================

TEST(ViewPropertyAnimatorTest, InterpolatorApplied) {
    auto looper = prepare_looper();
    ASSERT_NE(looper, nullptr);

    auto view = std::make_shared<View>();
    view->layout(0, 0, 100, 100);
    view->set_alpha(1.0f);

    auto vpa = view->animate();
    ASSERT_NE(vpa, nullptr);

    vpa->set_duration(100);
    vpa->set_interpolator(std::make_shared<DecelerateInterpolator>());
    vpa->alpha(0.0f);
    vpa->start();

    // Simulate 25ms of time passing (25% of 100ms duration)
    vpa->test_advance_time(25);

    auto choreo = Choreographer::get_instance();
    choreo->do_frame(Choreographer::system_time_nanos());

    // With decelerate at 25% elapsed:
    // fraction = 0.25, decelerate(0.25) = 1 - (1-0.25)^2 = 1 - 0.5625 = 0.4375
    // alpha = 1.0 + 0.4375 * (0.0 - 1.0) = 1.0 - 0.4375 = 0.5625
    float alpha = view->get_alpha();
    EXPECT_LT(alpha, 0.75f);  // decelerate moves faster at start
}

// ============================================================================
// Lifecycle tests
// ============================================================================

TEST(ViewPropertyAnimatorTest, EndActionFires) {
    auto looper = prepare_looper();
    ASSERT_NE(looper, nullptr);

    auto view = std::make_shared<View>();
    view->layout(0, 0, 100, 100);

    auto vpa = view->animate();
    ASSERT_NE(vpa, nullptr);

    std::atomic<bool> end_fired{false};
    vpa->with_end_action([&]() {
        end_fired.store(true);
    });

    vpa->set_duration(0);
    vpa->alpha(0.5f);
    vpa->start();

    auto choreo = Choreographer::get_instance();
    choreo->do_frame(Choreographer::system_time_nanos());

    EXPECT_TRUE(end_fired.load()) << "End action should have fired";
}

TEST(ViewPropertyAnimatorTest, StartActionFires) {
    auto looper = prepare_looper();
    ASSERT_NE(looper, nullptr);

    auto view = std::make_shared<View>();
    view->layout(0, 0, 100, 100);

    auto vpa = view->animate();

    std::atomic<bool> start_fired{false};
    vpa->with_start_action([&]() {
        start_fired.store(true);
    });

    vpa->set_duration(0);
    vpa->alpha(0.5f);
    vpa->start();

    EXPECT_TRUE(start_fired.load()) << "Start action should have fired";
}

TEST(ViewPropertyAnimatorTest, RapidStartCancelCycles) {
    auto looper = prepare_looper();
    auto view = std::make_shared<View>();
    view->layout(0, 0, 100, 100);

    auto vpa = view->animate();
    vpa->set_duration(1000);

    // Rapid start/cancel should not crash
    for (int i = 0; i < 10; i++) {
        vpa->alpha(0.5f);
        vpa->start();
        vpa->cancel();
    }

    // Final state should be canceled
    EXPECT_FALSE(vpa->is_running());
    EXPECT_FALSE(vpa->is_pending());
}

TEST(ViewPropertyAnimatorTest, StartAfterCancel) {
    auto looper = prepare_looper();
    auto view = std::make_shared<View>();
    view->layout(0, 0, 100, 100);
    view->set_alpha(1.0f);

    auto vpa = view->animate();
    vpa->set_duration(0);

    vpa->alpha(0.5f);
    vpa->start();
    vpa->cancel();

    // New animation after cancel should work
    vpa->alpha(0.8f);
    vpa->start();

    auto choreo = Choreographer::get_instance();
    choreo->do_frame(Choreographer::system_time_nanos());

    EXPECT_FLOAT_EQ(0.8f, view->get_alpha());
}

TEST(ViewPropertyAnimatorTest, GetView) {
    auto view = std::make_shared<View>();
    view->layout(0, 0, 100, 100);
    auto vpa = view->animate();
    ASSERT_NE(vpa, nullptr);

    auto retrieved = vpa->get_view();
    EXPECT_EQ(view, retrieved);
}
