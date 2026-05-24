#include <gtest/gtest.h>
#include <android/content/ClipData.h>

using namespace android::content;

TEST(ClipDataTest, CreatePlainText) {
    ClipDescription desc("label", {ClipDescription::MIMETYPE_TEXT_PLAIN});
    ClipData::Item item("Hello World");
    ClipData data(desc, item);

    EXPECT_EQ("label", data.getDescription().getLabel());
    EXPECT_EQ(1, data.getItemCount());
    EXPECT_EQ("Hello World", data.getItemAt(0).getText());
}

TEST(ClipDataTest, MultipleItems) {
    ClipDescription desc("label", {ClipDescription::MIMETYPE_TEXT_PLAIN});
    ClipData data(desc, ClipData::Item("item1"));
    data.addItem(ClipData::Item("item2"));

    EXPECT_EQ(2, data.getItemCount());
    EXPECT_EQ("item1", data.getItemAt(0).getText());
    EXPECT_EQ("item2", data.getItemAt(1).getText());
}
