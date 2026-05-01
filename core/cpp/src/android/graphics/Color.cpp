#include <android/graphics/Color.h>
#include <sstream>
#include <iomanip>
#include <algorithm>

namespace android::graphics {

uint32_t Color::argb(uint8_t a, uint8_t r, uint8_t g, uint8_t b) {
    return (static_cast<uint32_t>(a) << 24) |
           (static_cast<uint32_t>(r) << 16) |
           (static_cast<uint32_t>(g) << 8) |
           static_cast<uint32_t>(b);
}

uint32_t Color::rgb(uint8_t r, uint8_t g, uint8_t b) {
    return argb(255, r, g, b);
}

uint8_t Color::getRed(uint32_t color) {
    return static_cast<uint8_t>((color >> 16) & 0xFF);
}

uint8_t Color::getGreen(uint32_t color) {
    return static_cast<uint8_t>((color >> 8) & 0xFF);
}

uint8_t Color::getBlue(uint32_t color) {
    return static_cast<uint8_t>(color & 0xFF);
}

uint8_t Color::getAlpha(uint32_t color) {
    return static_cast<uint8_t>((color >> 24) & 0xFF);
}

uint32_t Color::setColorAlpha(uint32_t color, uint8_t alpha) {
    return (color & 0x00FFFFFF) | (static_cast<uint32_t>(alpha) << 24);
}

uint32_t Color::setAlphaColor(uint8_t alpha, uint32_t color) {
    return (static_cast<uint32_t>(alpha) << 24) | (color & 0x00FFFFFF);
}

namespace {

std::string to_lower(std::string_view s) {
    std::string result(s);
    std::ranges::transform(result, result.begin(), [](unsigned char c) { return std::tolower(c); });
    return result;
}

} // anonymous namespace

std::expected<uint32_t, std::string> Color::parseColor(std::string_view str) {
    if (str.empty()) {
        return std::unexpected("empty color string");
    }

    // "transparent"
    if (str == "transparent") {
        return TRANSPARENT;
    }

    auto s = to_lower(str);

    // #android:name
    if (s.starts_with("#android:")) {
        auto name = s.substr(9);
        if (name == "red") return RED;
        if (name == "green") return GREEN;
        if (name == "blue") return BLUE;
        if (name == "black") return BLACK;
        if (name == "white") return WHITE;
        if (name == "cyan") return CYAN;
        if (name == "magenta") return MAGENTA;
        if (name == "yellow") return YELLOW;
        if (name == "transparent") return TRANSPARENT;
        return std::unexpected("unknown color name: " + std::string(name));
    }

    // Hex formats
    if (s.starts_with("0x") || s.starts_with("#")) {
        auto hex = s;
        if (hex.starts_with("0x")) {
            hex = hex.substr(2);
        } else {
            hex = hex.substr(1);
        }

        if (hex.length() < 3 || hex.length() > 8) {
            return std::unexpected("invalid hex length");
        }

        auto val = static_cast<uint32_t>(std::stoul(std::string(hex), nullptr, 16));

        switch (hex.length()) {
            case 3: { // #RGB → #FFRRGGBB (each digit doubled)
                auto r = static_cast<uint8_t>(std::stoi(std::string(1, hex[0]), nullptr, 16) * 17);
                auto g = static_cast<uint8_t>(std::stoi(std::string(1, hex[1]), nullptr, 16) * 17);
                auto b = static_cast<uint8_t>(std::stoi(std::string(1, hex[2]), nullptr, 16) * 17);
                return argb(255, r, g, b);
            }
            case 6: // #RRGGBB → #FFRRGGBB
                return rgb(
                    static_cast<uint8_t>((val >> 16) & 0xFF),
                    static_cast<uint8_t>((val >> 8) & 0xFF),
                    static_cast<uint8_t>(val & 0xFF));
            case 8: // #AARRGGBB
                return val;
            default:
                return std::unexpected("invalid hex length: " + std::to_string(hex.length()));
        }
    }

    // Plain named colors (without #android: prefix)
    if (s == "red") return RED;
    if (s == "green") return GREEN;
    if (s == "blue") return BLUE;
    if (s == "black") return BLACK;
    if (s == "white") return WHITE;
    if (s == "cyan") return CYAN;
    if (s == "magenta") return MAGENTA;
    if (s == "yellow") return YELLOW;

    return std::unexpected("unrecognized color: " + std::string(str));
}

std::string Color::toArgbString(uint32_t color) {
    std::ostringstream oss;
    oss << "#" << std::hex << std::uppercase << std::setfill('0') << std::setw(8)
        << color;
    return oss.str();
}

} // namespace android::graphics
