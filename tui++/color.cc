#include <color.hpp>

#include <string>
#include <format>

namespace tuipp {
    inline namespace v0_0_1 {
        Color::Color() = default;
        Color::Color(uint8_t r, uint8_t g, uint8_t b): r(r), g(g), b(b) {}
        Color Color::fromHex(std::string_view hex) {
            uint8_t r, g, b;

            if (hex[0] == '#') // Ignore first char
                hex = hex.substr(1);

            const std::string_view r_str = hex.substr(0, 2);
            const std::string_view g_str = hex.substr(2, 2);
            const std::string_view b_str = hex.substr(4, 2);

            r = std::stoul((std::string)r_str, nullptr, 16);
            g = std::stoul((std::string)g_str, nullptr, 16);
            b = std::stoul((std::string)b_str, nullptr, 16);

            return Color(r, g, b);
        }

        Color Color::fromRGB(uint8_t r, uint8_t g, uint8_t b) {
            return Color(r, g, b);
        }

        std::string Color::toANSI() {
            return std::format("\033[38;2;{};{};{}m", r, g, b);
        }

        std::string Color::ANSIdefault() {
            return "\033[0m";
        }
    }
}
