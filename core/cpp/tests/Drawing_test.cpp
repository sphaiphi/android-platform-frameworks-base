#include <gtest/gtest.h>
#include <android/view/View.h>
#include <android/view/ViewGroup.h>
#include <android/view/ViewRootImpl.h>
#include <android/graphics/Canvas.h>
#include <android/graphics/RenderNode.h>
#include <memory>
#include <vector>
#include <string>

using namespace android::view;
using namespace android::graphics;

class MockCanvas : public Canvas {
public:
    MockCanvas() : Canvas(1, 1) {}
    std::vector<std::string> operations;
    void draw_rect(int32_t l, int32_t t, int32_t r, int32_t b) override {
        operations.push_back("draw_rect");
    }
};

class DrawingMockView : public View {
public:
    bool on_draw_called = false;
    void on_draw(Canvas& canvas) override {
        on_draw_called = true;
        canvas.draw_rect(0, 0, 100, 100);
    }
};

class MockRenderNode : public RenderNode {
public:
    explicit MockRenderNode(const std::string& name) : RenderNode(name) {}
    bool recording = false;
    bool display_list = false;
    MockCanvas mock_canvas;

    Canvas* begin_recording(int32_t /*width*/, int32_t /*height*/) override {
        recording = true;
        return &mock_canvas;
    }

    void end_recording() override {
        recording = false;
        display_list = true;
    }

    bool has_display_list() const override {
        return display_list;
    }
};

TEST(DrawingTest, DrawTriggersOnDraw) {
    DrawingMockView view;
    MockCanvas canvas;
    
    view.draw(canvas);
    
    EXPECT_TRUE(view.on_draw_called);
    ASSERT_EQ(canvas.operations.size(), 1);
    EXPECT_EQ(canvas.operations[0], "draw_rect");
}

TEST(DrawingTest, RenderNodeRecording) {
    MockRenderNode render_node("TestNode");
    EXPECT_FALSE(render_node.has_display_list());
    
    Canvas* canvas = render_node.begin_recording(100, 100);
    ASSERT_NE(canvas, nullptr);
    EXPECT_TRUE(render_node.recording);
    
    canvas->draw_rect(0, 0, 50, 50);
    render_node.end_recording();
    
    EXPECT_FALSE(render_node.recording);
    EXPECT_TRUE(render_node.has_display_list());
    
    MockCanvas* mock_canvas = static_cast<MockCanvas*>(canvas);
    ASSERT_EQ(mock_canvas->operations.size(), 1);
    EXPECT_EQ(mock_canvas->operations[0], "draw_rect");
}

TEST(DrawingTest, HierarchicalDrawing) {
    auto parent = std::make_shared<ViewGroup>();
    auto child1 = std::make_shared<DrawingMockView>();
    auto child2 = std::make_shared<DrawingMockView>();
    
    parent->add_view(child1);
    parent->add_view(child2);
    
    MockCanvas canvas;
    parent->draw(canvas);
    
    EXPECT_TRUE(child1->on_draw_called);
    EXPECT_TRUE(child2->on_draw_called);
    EXPECT_EQ(canvas.operations.size(), 2);
}

class ViewRootImplDrawingTest : public ::testing::Test {
protected:
    void SetUp() override {
        root = std::make_shared<ViewRootImpl>();
        view = std::make_shared<DrawingMockView>();
        root->set_view(view);
    }

    std::shared_ptr<ViewRootImpl> root;
    std::shared_ptr<DrawingMockView> view;
};

TEST_F(ViewRootImplDrawingTest, PerformDrawCallsViewDraw) {
    // We need a way to provide a Canvas to ViewRootImpl or have it create one.
    // For now, let's assume perform_draw() initiates drawing.
    root->perform_traversals();
    EXPECT_TRUE(view->on_draw_called);
}
