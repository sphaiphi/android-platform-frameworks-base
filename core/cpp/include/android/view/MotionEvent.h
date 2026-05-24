#pragma once

#include <cstdint>
#include <vector>

namespace android {
namespace view {

class MotionEvent {
public:
    enum Action {
        ACTION_DOWN = 0,
        ACTION_UP = 1,
        ACTION_MOVE = 2,
        ACTION_CANCEL = 3,
        ACTION_OUTSIDE = 4,
        ACTION_POINTER_DOWN = 5,
        ACTION_POINTER_UP = 6,
        ACTION_HOVER_MOVE = 7,
        ACTION_SCROLL = 8,
        ACTION_HOVER_ENTER = 9,
        ACTION_HOVER_EXIT = 10,
    };

    MotionEvent(Action action, float x, float y)
        : action_(action), x_(x), y_(y),
          device_id_(0), source_(0x00000002), event_time_(0), pointer_count_(1) {}

    MotionEvent(Action action, float x, float y,
                int32_t device_id, uint32_t source,
                int64_t event_time,
                uint32_t pointer_count = 1)
        : action_(action), x_(x), y_(y),
          device_id_(device_id), source_(source),
          event_time_(event_time), pointer_count_(pointer_count) {}

    auto get_action() const -> Action { return action_; }
    auto get_action_masked() const -> Action {
        return static_cast<Action>(action_ & 0x000000ff);
    }
    auto get_action_index() const -> uint32_t {
        return (action_ >> 8) & 0x000000ff;
    }
    auto get_x() const -> float { return x_; }
    auto get_y() const -> float { return y_; }
    auto get_device_id() const -> int32_t { return device_id_; }
    auto get_source() const -> uint32_t { return source_; }
    auto get_event_time() const -> int64_t { return event_time_; }
    auto get_pointer_count() const -> uint32_t { return pointer_count_; }

    auto get_pointer_id(uint32_t index) const -> uint32_t {
        if (index < pointer_ids_.size()) {
            return pointer_ids_[index];
        }
        return static_cast<uint32_t>(index);
    }

    auto get_pointer_x(uint32_t index) const -> float {
        if (index < pointer_coords_.size()) {
            return pointer_coords_[index].first;
        }
        return x_;
    }
    auto get_pointer_y(uint32_t index) const -> float {
        if (index < pointer_coords_.size()) {
            return pointer_coords_[index].second;
        }
        return y_;
    }

    auto get_history_size() const -> uint32_t { return static_cast<uint32_t>(history_.size()); }

    struct HistoricalEntry {
        float x;
        float y;
        uint32_t size;
    };
    auto get_history_entry(uint32_t index) const -> HistoricalEntry {
        if (index < history_.size()) {
            return history_[index];
        }
        return {0.f, 0.f, 0};
    }

    void offset_location(float dx, float dy) {
        x_ += dx;
        y_ += dy;
        for (auto& entry : history_) {
            entry.x += dx;
            entry.y += dy;
        }
    }

    void add_history(float hx, float hy, uint32_t hsize) {
        history_.push_back({hx, hy, hsize});
    }

    void clear_history() {
        history_.clear();
    }

private:
    Action action_;
    float x_;
    float y_;
    int32_t device_id_;
    uint32_t source_;
    int64_t event_time_;
    uint32_t pointer_count_;
    std::vector<uint32_t> pointer_ids_;
    std::vector<std::pair<float, float>> pointer_coords_;
    std::vector<HistoricalEntry> history_;
};

} // namespace view
} // namespace android
