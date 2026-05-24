#pragma once

#include <string>
#include <vector>
#include <optional>
#include <android/binder_parcel.h>
#include <android/binder_status.h>

namespace android::content {

/**
 * Meta-data describing the contents of a ClipData.
 */
class ClipDescription {
public:
    static const inline std::string MIMETYPE_TEXT_PLAIN = "text/plain";
    static const inline std::string MIMETYPE_TEXT_HTML = "text/html";
    static const inline std::string MIMETYPE_TEXT_URILIST = "text/uri-list";
    static const inline std::string MIMETYPE_TEXT_INTENT = "text/vnd.android.intent";

    ClipDescription(std::string label, std::vector<std::string> mimeTypes);
    ClipDescription() = default;

    [[nodiscard]] auto getLabel() const -> const std::string&;
    [[nodiscard]] auto getMimeTypeCount() const -> int;
    [[nodiscard]] auto getMimeType(int index) const -> const std::string&;
    [[nodiscard]] auto hasMimeType(const std::string& mimeType) const -> bool;

    auto writeToParcel(AParcel* parcel) const -> binder_status_t;
    auto readFromParcel(const AParcel* parcel) -> binder_status_t;

private:
    std::string mLabel;
    std::vector<std::string> mMimeTypes;
};

} // namespace android::content
