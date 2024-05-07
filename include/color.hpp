#pragma once

#include <cstdint>

#include <string_view>
#include <string>

namespace tuipp {
    inline namespace v0_0_1 {
        /**
         * @class Color
         * @brief Stores an RGB color
         *
         */
        struct Color {
            uint8_t r;
            uint8_t g;
            uint8_t b;

            /**
             * @brief Constructs a tuipp::Color from a hex representation
             *
             * @param hex Hex representation
             * @return Color
             */
            static Color fromHex(std::string_view hex);

            /**
             * @brief Constructs a tuipp::Color from an rgb representation
             *
             * @param r Red
             * @param g Green
             * @param b Blue
             * @return Color
             */
            static Color fromRGB(uint8_t r, uint8_t g, uint8_t b);

            /**
             * @brief Converts color to an ANSI escape sequence
             */
            std::string toANSI();

            /**
             * @brief Generates the default ANSI color
             */
            static std::string ANSIdefault();

            private: 
                Color();
                Color(uint8_t r, uint8_t g, uint8_t b);
        };
    }
}
