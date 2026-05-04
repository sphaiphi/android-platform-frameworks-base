#include <gtest/gtest.h>
#include <android/view/InputChannel.h>
#include <memory>

namespace android::view {

TEST(InputChannelTest, DefaultConstructorIsNull) {
    InputChannel channel;
    EXPECT_FALSE(channel.is_valid());
    EXPECT_TRUE(channel.name().empty());
}

TEST(InputChannelTest, FromNativeHandle) {
    void* fake_fd = reinterpret_cast<void*>(42);
    InputChannel channel("test_channel", fake_fd);
    EXPECT_TRUE(channel.is_valid());
    EXPECT_EQ("test_channel", channel.name());
    EXPECT_EQ(fake_fd, channel.get_native_handle());
}

TEST(InputChannelTest, NullHandleIsInvalid) {
    InputChannel channel("orphan", nullptr);
    EXPECT_FALSE(channel.is_valid());
    EXPECT_EQ("orphan", channel.name());
}

TEST(InputChannelTest, CopyConstructor) {
    void* fake_fd = reinterpret_cast<void*>(99);
    InputChannel a("dup_channel", fake_fd);
    InputChannel b(a);
    EXPECT_EQ("dup_channel", b.name());
    EXPECT_TRUE(b.is_valid());
}

TEST(InputChannelTest, SharedPtrConstruction) {
    void* fake_fd = reinterpret_cast<void*>(77);
    auto channel = std::make_shared<InputChannel>("shared_channel", fake_fd);
    EXPECT_TRUE(channel->is_valid());
}

} // namespace android::view
