#pragma once

#include <string>
#include <vector>
#include <memory>
#include <android/content/ClipDescription.h>
#include <android/net/Uri.h>
#include <android/binder_parcel.h>
#include <android/binder_status.h>

namespace android::content {

class Intent; // Forward declaration

/**
 * Representation of clipped data on the clipboard.
 */
class ClipData {
public:
    class Item {
    public:
        Item(std::string text);
        Item(std::shared_ptr<Intent> intent);
        Item(net::Uri uri);
        Item(std::string text, std::shared_ptr<Intent> intent, net::Uri uri);
        Item();
        ~Item();

        [[nodiscard]] auto getText() const -> const std::string&;
        [[nodiscard]] auto getIntent() const -> std::shared_ptr<Intent>;
        [[nodiscard]] auto getUri() const -> const net::Uri&;

        auto writeToParcel(AParcel* parcel) const -> binder_status_t;
        auto readFromParcel(const AParcel* parcel) -> binder_status_t;

    private:
        std::string mText;
        std::string mHtmlText;
        std::shared_ptr<Intent> mIntent;
        net::Uri mUri;
    };

    ClipData(ClipDescription description, Item item);
    ClipData(const ClipData& other);
    ClipData() = default;
    ~ClipData() = default;

    [[nodiscard]] auto getDescription() const -> const ClipDescription&;
    auto addItem(Item item) -> void;
    [[nodiscard]] auto getItemCount() const -> int;
    [[nodiscard]] auto getItemAt(int index) const -> const Item&;

    auto writeToParcel(AParcel* parcel) const -> binder_status_t;
    auto readFromParcel(const AParcel* parcel) -> binder_status_t;

private:
    ClipDescription mClipDescription;
    std::vector<Item> mItems;
};

} // namespace android::content
