#include <gtest/gtest.h>
#include <android/app/Application.h>
#include <android/app/ContextImpl.h>

using namespace android::app;

class TestApplication : public Application {
public:
    bool created = false;
    void on_create() override {
        Application::on_create();
        created = true;
    }
};

TEST(ApplicationTest, Lifecycle) {
    TestApplication app;
    auto context = std::make_shared<ContextImpl>();
    app.attach_base_context(context);
    
    app.on_create();
    EXPECT_TRUE(app.created);
}
