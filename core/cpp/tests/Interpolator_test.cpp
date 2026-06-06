#include <gtest/gtest.h>
#include <android/view/Interpolator.h>
#include <android/view/Interpolator.h>

#include <memory>

using namespace android::view;

// ============================================================================
// Interpolator interface tests
// ============================================================================

// Test: Interpolator is abstract (cannot instantiate directly)
TEST(InterpolatorTest, InterfaceIsAbstract) {
    // Interpolator should be a pure virtual interface —
    // we test by creating a concrete subclass.
    struct TestInterpolator : Interpolator {
        float getInterpolation(float input) override {
            return input;
        }
    };

    auto interp = std::make_unique<TestInterpolator>();
    ASSERT_NE(interp, nullptr);
}

// Test: Interpolator returns clamped output for inputs outside [0, 1]
TEST(InterpolatorTest, OutputIsClamped) {
    struct TestInterpolator : Interpolator {
        float getInterpolation(float input) override {
            return input;
        }
    };

    auto interp = std::make_unique<TestInterpolator>();
    // Even with identity interpolation, the interface contract
    // requires output clamping to [0, 1]
    EXPECT_FLOAT_EQ(0.0f, interp->getInterpolation(-0.5f));
    EXPECT_FLOAT_EQ(1.0f, interp->getInterpolation(1.5f));
}

// Test: getInterpolation(0.0f) always returns 0.0f
TEST(InterpolatorTest, StartPointIsZero) {
    struct TestInterpolator : Interpolator {
        float getInterpolation(float input) override {
            return input;
        }
    };

    auto interp = std::make_unique<TestInterpolator>();
    EXPECT_FLOAT_EQ(0.0f, interp->getInterpolation(0.0f));
}

// Test: getInterpolation(1.0f) always returns 1.0f
TEST(InterpolatorTest, EndPointIsOne) {
    struct TestInterpolator : Interpolator {
        float getInterpolation(float input) override {
            return input;
        }
    };

    auto interp = std::make_unique<TestInterpolator>();
    EXPECT_FLOAT_EQ(1.0f, interp->getInterpolation(1.0f));
}

// ============================================================================
// LinearInterpolator tests
// ============================================================================

TEST(InterpolatorTest, LinearIdentity) {
    auto interp = std::make_shared<LinearInterpolator>();
    EXPECT_FLOAT_EQ(0.0f, interp->getInterpolation(0.0f));
    EXPECT_FLOAT_EQ(0.25f, interp->getInterpolation(0.25f));
    EXPECT_FLOAT_EQ(0.5f, interp->getInterpolation(0.5f));
    EXPECT_FLOAT_EQ(0.75f, interp->getInterpolation(0.75f));
    EXPECT_FLOAT_EQ(1.0f, interp->getInterpolation(1.0f));
}

TEST(InterpolatorTest, LinearClampsOutsideRange) {
    auto interp = std::make_shared<LinearInterpolator>();
    EXPECT_FLOAT_EQ(0.0f, interp->getInterpolation(-0.5f));
    EXPECT_FLOAT_EQ(1.0f, interp->getInterpolation(1.5f));
}

// ============================================================================
// AccelerateDecelerateInterpolator tests
// ============================================================================

TEST(InterpolatorTest, AccelerateDecelerateBoundaries) {
    auto interp = std::make_shared<AccelerateDecelerateInterpolator>();
    EXPECT_FLOAT_EQ(0.0f, interp->getInterpolation(0.0f));
    EXPECT_FLOAT_EQ(1.0f, interp->getInterpolation(1.0f));
}

TEST(InterpolatorTest, AccelerateDecelerateSymmetric) {
    auto interp = std::make_shared<AccelerateDecelerateInterpolator>();
    // Symmetric around 0.5
    float q025 = interp->getInterpolation(0.25f);
    float q75 = interp->getInterpolation(0.75f);
    EXPECT_FLOAT_EQ(q025, q75);
}

TEST(InterpolatorTest, AccelerateDecelerateAcceleratesAtStart) {
    auto interp = std::make_shared<AccelerateDecelerateInterpolator>();
    // At 0.25, should be below the linear line (accelerating)
    EXPECT_LT(interp->getInterpolation(0.25f), 0.25f);
}

// ============================================================================
// DecelerateInterpolator tests
// ============================================================================

TEST(InterpolatorTest, DecelerateBoundaries) {
    auto interp = std::make_shared<DecelerateInterpolator>();
    EXPECT_FLOAT_EQ(0.0f, interp->getInterpolation(0.0f));
    EXPECT_FLOAT_EQ(1.0f, interp->getInterpolation(1.0f));
}

TEST(InterpolatorTest, DecelerateExactValues) {
    auto interp = std::make_shared<DecelerateInterpolator>();
    // 1 - (1 - 0.75)^2 = 1 - 0.0625 = 0.9375
    EXPECT_FLOAT_EQ(0.9375f, interp->getInterpolation(0.75f));
    // 1 - (1 - 0.5)^2 = 1 - 0.25 = 0.75
    EXPECT_FLOAT_EQ(0.75f, interp->getInterpolation(0.5f));
}

TEST(InterpolatorTest, DecelerateFastAtStart) {
    auto interp = std::make_shared<DecelerateInterpolator>();
    // At 0.25, should be above the linear line (decelerating)
    EXPECT_GT(interp->getInterpolation(0.25f), 0.25f);
}
