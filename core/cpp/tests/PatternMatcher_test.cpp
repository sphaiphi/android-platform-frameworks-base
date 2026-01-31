#include <gtest/gtest.h>
#include <android/os/PatternMatcher.h>

using namespace android::os;

TEST(PatternMatcherTest, LiteralMatch) {
    PatternMatcher matcher("test", PatternMatcher::PATTERN_LITERAL);
    EXPECT_TRUE(matcher.match("test"));
    EXPECT_FALSE(matcher.match("test1"));
    EXPECT_FALSE(matcher.match("tes"));
}

TEST(PatternMatcherTest, PrefixMatch) {
    PatternMatcher matcher("test", PatternMatcher::PATTERN_PREFIX);
    EXPECT_TRUE(matcher.match("test"));
    EXPECT_TRUE(matcher.match("test1"));
    EXPECT_TRUE(matcher.match("testing"));
    EXPECT_FALSE(matcher.match("tes"));
    EXPECT_FALSE(matcher.match("atest"));
}

TEST(PatternMatcherTest, SuffixMatch) {
    PatternMatcher matcher("test", PatternMatcher::PATTERN_SUFFIX);
    EXPECT_TRUE(matcher.match("test"));
    EXPECT_TRUE(matcher.match("mytest"));
    EXPECT_FALSE(matcher.match("test1"));
    EXPECT_FALSE(matcher.match("tes"));
}

TEST(PatternMatcherTest, SimpleGlobMatch) {
    // . matches any char, * matches 0 or more of previous
    PatternMatcher matcher("ab*c", PatternMatcher::PATTERN_SIMPLE_GLOB);
    EXPECT_TRUE(matcher.match("ac"));
    EXPECT_TRUE(matcher.match("abc"));
    EXPECT_TRUE(matcher.match("abbbc"));
    EXPECT_FALSE(matcher.match("abbbd"));

    PatternMatcher matcher2("a.*c", PatternMatcher::PATTERN_SIMPLE_GLOB);
    EXPECT_TRUE(matcher2.match("ac"));
    EXPECT_TRUE(matcher2.match("abc"));
    EXPECT_TRUE(matcher2.match("axyzc"));
    EXPECT_FALSE(matcher2.match("ax"));
    
    PatternMatcher matcher3(".*", PatternMatcher::PATTERN_SIMPLE_GLOB);
    EXPECT_TRUE(matcher3.match(""));
    EXPECT_TRUE(matcher3.match("anything"));
}

TEST(PatternMatcherTest, Escaping) {
    PatternMatcher matcher("a\\*b", PatternMatcher::PATTERN_SIMPLE_GLOB);
    EXPECT_TRUE(matcher.match("a*b"));
    EXPECT_FALSE(matcher.match("ab"));
    EXPECT_FALSE(matcher.match("aaab"));
}

