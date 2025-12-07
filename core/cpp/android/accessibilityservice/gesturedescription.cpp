// file: gesturedescription.cpp
module android.accessibilityservice;

import <stdexcept>;
import <atomic>;
import <algorithm>;

// This would be the actual NDK header
// #include <android/binder_parcel.h> 

namespace android::accessibilityservice {

// Stroke ID counter, made thread-safe with std::atomic
static std::atomic<int32_t> s_next_stroke_id = 0;

//--- StrokeDescription Implementation ---//

StrokeDescription::StrokeDescription(Path path, milliseconds start_time, milliseconds duration, bool will_be_continued)
    : path_(std::move(path)),
      start_time_(start_time),
      duration_(duration),
      will_be_continued_(will_be_continued),
      id_{s_next_stroke_id++},
      continued_stroke_id_{}
{
    if (duration_ <= 0ms) throw std::invalid_argument("Duration must be positive");
    if (start_time_ < 0ms) throw std::invalid_argument("Start time must not be negative");
    if (path_.points.empty()) throw std::invalid_argument("Path must not be empty");
}

StrokeDescription::StrokeDescription(Path path, milliseconds start_time, milliseconds duration, bool will_be_continued, StrokeId continued_id)
    : path_(std::move(path)),
      start_time_(start_time),
      duration_(duration),
      will_be_continued_(will_be_continued),
      id_{s_next_stroke_id++},
      continued_stroke_id_{continued_id}
{
    // Internal constructor assumes valid arguments
}

auto StrokeDescription::continue_stroke(Path path, milliseconds start_time, milliseconds duration, bool will_be_continued) const
-> std::expected<StrokeDescription, std::string>
{
    if (!will_be_continued_) {
        return std::unexpected("This stroke was not marked as continuable.");
    }
    return StrokeDescription{std::move(path), start_time, duration, will_be_continued, id_};
}

auto StrokeDescription::get_path() const -> const Path& { return path_; }
auto StrokeDescription::get_start_time() const -> milliseconds { return start_time_; }
auto StrokeDescription::get_duration() const -> milliseconds { return duration_; }
auto StrokeDescription::will_continue() const -> bool { return will_be_continued_; }
auto StrokeDescription::get_id() const -> StrokeId { return id_; }
auto StrokeDescription::get_continued_id() const -> std::optional<StrokeId> { return continued_stroke_id_; }

//--- GestureDescription Implementation ---//

GestureDescription::GestureDescription(std::vector<StrokeDescription> strokes, DisplayId display_id)
    : strokes_(std::move(strokes)), display_id_(display_id) {}

auto GestureDescription::get_stroke_count() const -> size_t {
    return strokes_.size();
}

auto GestureDescription::get_stroke(size_t index) const -> const StrokeDescription& {
    return strokes_.at(index); // .at() for bounds checking
}

auto GestureDescription::get_display_id() const -> DisplayId {
    return display_id_;
}

} // namespace android::accessibilityservice