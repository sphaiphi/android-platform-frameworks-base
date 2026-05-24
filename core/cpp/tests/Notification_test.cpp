#include <gtest/gtest.h>
#include <android/app/Notification.h>

using namespace android::app;

TEST(NotificationTest, Builder) {
    Notification::Builder builder(nullptr, "test_channel");
    builder.set_content_title("Title")
           .set_content_text("Text")
           .set_small_icon(123);
    
    auto notification = builder.build();
    EXPECT_EQ(notification->get_channel_id(), "test_channel");
}
