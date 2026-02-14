#include <gtest/gtest.h>
#include <android/app/Exceptions.h>
#include <android/app/RemoteAction.h>

using namespace android::app;

TEST(ExceptionTest, ServiceStartNotAllowedExceptionFactory) {
    auto fgs_ex = ServiceStartNotAllowedException::newInstance(true, "fgs error");
    EXPECT_NE(dynamic_cast<ForegroundServiceStartNotAllowedException*>(fgs_ex.get()), nullptr);
    EXPECT_STREQ(fgs_ex->what(), "fgs error");

    auto bg_ex = ServiceStartNotAllowedException::newInstance(false, "bg error");
    EXPECT_NE(dynamic_cast<BackgroundServiceStartNotAllowedException*>(bg_ex.get()), nullptr);
    EXPECT_STREQ(bg_ex->what(), "bg error");
}

TEST(ExceptionTest, RecoverableSecurityException) {
    auto action = std::make_shared<RemoteAction>("title", "desc", nullptr);
    RecoverableSecurityException ex("msg", "user msg", action);
    
    EXPECT_STREQ(ex.what(), "msg");
    EXPECT_EQ(ex.get_user_message(), "user msg");
    EXPECT_EQ(ex.get_user_action(), action);
}

TEST(ExceptionTest, Hierarchy) {
    auto fgs_ex = ServiceStartNotAllowedException::newInstance(true, "error");
    
    EXPECT_NE(dynamic_cast<ServiceStartNotAllowedException*>(fgs_ex.get()), nullptr);
    EXPECT_NE(dynamic_cast<IllegalStateException*>(fgs_ex.get()), nullptr);
    EXPECT_NE(dynamic_cast<AndroidException*>(fgs_ex.get()), nullptr);
    EXPECT_NE(dynamic_cast<std::runtime_error*>(fgs_ex.get()), nullptr);
}
