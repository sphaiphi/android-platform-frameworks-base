#include <gtest/gtest.h>
#include <android/net/Uri.h>

using namespace android::net;

TEST(UriTest, ParseHierarchical) {
    auto uri = Uri::parse("http://google.com/path?q=android#fragment");
    EXPECT_EQ("http", uri.getScheme().value_or(""));
    EXPECT_EQ("google.com", uri.getAuthority().value_or(""));
    EXPECT_EQ("/path", uri.getPath().value_or(""));
    EXPECT_EQ("q=android", uri.getQuery().value_or(""));
    EXPECT_EQ("fragment", uri.getFragment().value_or(""));
    EXPECT_TRUE(uri.isHierarchical());
    EXPECT_FALSE(uri.isOpaque());
}

TEST(UriTest, ParseOpaque) {
    auto uri = Uri::parse("mailto:nobody@google.com");
    EXPECT_EQ("mailto", uri.getScheme().value_or(""));
    EXPECT_EQ("nobody@google.com", uri.getSchemeSpecificPart());
    EXPECT_TRUE(uri.isOpaque());
    EXPECT_FALSE(uri.isHierarchical());
}

TEST(UriTest, ParseRelative) {
    auto uri = Uri::parse("/path/to/thing");
    EXPECT_TRUE(uri.isRelative());
    EXPECT_EQ("/path/to/thing", uri.getPath().value_or(""));
}

TEST(UriTest, BuildUpon) {
    auto uri = Uri::parse("http://google.com/path");
    auto built = uri.buildUpon()
        .appendPath("subpath")
        .appendQueryParameter("key", "value")
        .build();
    EXPECT_EQ("http://google.com/path/subpath?key=value", built.toString());
}

TEST(UriTest, Equality) {
    auto uri1 = Uri::parse("http://google.com");
    auto uri2 = Uri::parse("http://google.com");
    auto uri3 = Uri::parse("https://google.com");
    EXPECT_EQ(uri1, uri2);
    EXPECT_NE(uri1, uri3);
}
