#include <gtest/gtest.h>
#include <android/content/IntentFilter.h>

using namespace android::content;

TEST(IntentFilterTest, ActionTests) {
    IntentFilter filter;
    filter.addAction("ACTION_VIEW");
    filter.addAction("ACTION_EDIT");

    EXPECT_TRUE(filter.hasAction("ACTION_VIEW"));
    EXPECT_TRUE(filter.hasAction("ACTION_EDIT"));
    EXPECT_FALSE(filter.hasAction("ACTION_MAIN"));
    EXPECT_EQ(2, filter.countActions());
    
    EXPECT_TRUE(filter.matchAction("ACTION_VIEW"));
    EXPECT_FALSE(filter.matchAction("ACTION_MAIN"));
}

TEST(IntentFilterTest, CategoryTests) {
    IntentFilter filter;
    filter.addCategory("CATEGORY_DEFAULT");
    
    EXPECT_TRUE(filter.hasCategory("CATEGORY_DEFAULT"));
    EXPECT_FALSE(filter.hasCategory("CATEGORY_BROWSABLE"));
    
    std::vector<std::string> intentCategories = {"CATEGORY_DEFAULT"};
    auto mismatch = filter.matchCategories(intentCategories);
    EXPECT_FALSE(mismatch.has_value()); // No mismatch

    std::vector<std::string> intentCategories2 = {"CATEGORY_DEFAULT", "CATEGORY_BROWSABLE"};
    mismatch = filter.matchCategories(intentCategories2);
    EXPECT_TRUE(mismatch.has_value());
    EXPECT_EQ("CATEGORY_BROWSABLE", mismatch.value());
}

TEST(IntentFilterTest, DataSchemeTests) {
    IntentFilter filter;
    filter.addDataScheme("http");
    
    EXPECT_TRUE(filter.hasDataScheme("http"));
    EXPECT_FALSE(filter.hasDataScheme("https"));
}

TEST(IntentFilterTest, DataAuthorityTests) {
    IntentFilter filter;
    filter.addDataScheme("http");
    filter.addDataAuthority("example.com", "80");
    
    EXPECT_EQ(1, filter.countDataAuthorities());
    EXPECT_EQ("example.com", filter.getDataAuthority(0).host);
    EXPECT_EQ(80, filter.getDataAuthority(0).port);
}

TEST(IntentFilterTest, DataPathTests) {
    IntentFilter filter;
    filter.addDataPath("/foo", android::os::PatternMatcher::PATTERN_LITERAL);
    filter.addDataPath("/bar.*", android::os::PatternMatcher::PATTERN_SIMPLE_GLOB);
    
    EXPECT_EQ(2, filter.countDataPaths());
}

TEST(IntentFilterTest, MatchDataTests) {
    IntentFilter filter;
    filter.addDataScheme("http");
    filter.addDataAuthority("example.com", "80");
    filter.addDataPath("/test", android::os::PatternMatcher::PATTERN_LITERAL);
    filter.addDataType("image/*");

    // Exact match (MIME type match is highest priority)
    int result = filter.matchData("image/png", "http", "example.com", 80, "/test");
    EXPECT_GE(result, 0);
    EXPECT_EQ(IntentFilter::MATCH_CATEGORY_TYPE + IntentFilter::MATCH_ADJUSTMENT_NORMAL, result);

    // Mismatched type
    result = filter.matchData("video/mp4", "http", "example.com", 80, "/test");
    EXPECT_EQ(IntentFilter::NO_MATCH_TYPE, result);

    // Mismatched scheme
    result = filter.matchData("image/png", "https", "example.com", 80, "/test");
    EXPECT_EQ(IntentFilter::NO_MATCH_DATA, result);

    // Mismatched host
    result = filter.matchData("image/png", "http", "wrong.com", 80, "/test");
    EXPECT_EQ(IntentFilter::NO_MATCH_DATA, result);

    // Mismatched port
    result = filter.matchData("image/png", "http", "example.com", 8080, "/test");
    EXPECT_EQ(IntentFilter::NO_MATCH_DATA, result);

    // Mismatched path
    result = filter.matchData("image/png", "http", "example.com", 80, "/wrong");
    EXPECT_EQ(IntentFilter::NO_MATCH_DATA, result);
}

TEST(IntentFilterTest, AuthorityWildcardTests) {
    IntentFilter filter;
    filter.addDataScheme("http");
    filter.addDataAuthority("*.example.com", ""); // wild = true, host = ".example.com"
    
    EXPECT_GE(filter.matchData("", "http", "foo.example.com", -1, ""), 0);
    // Android's *.example.com matches subdomains but not the base domain itself in this implementation
    EXPECT_LT(filter.matchData("", "http", "example.com", -1, ""), 0);
    EXPECT_LT(filter.matchData("", "http", "other.com", -1, ""), 0);
}