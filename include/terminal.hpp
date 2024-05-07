#pragma once
#include <color.hpp>

#include <cstdint>

#include <utility>
#include <string>
#include <string_view>
#include <format>

#include <termios.h>

namespace tuipp {
    inline namespace v0_0_1 {
        extern termios original_terminal_settings;

        /**
         * @brief Linux reimplementation of WIN32 kbhit
         *
         * @return true if there is data in stdin
         */
        bool kbhit();

        /**
         * @brief Puts term into raw mode
         */
        void raw_terminal();

        /**
         * @brief Gets the current position of the terminal cursor
         */
        std::pair<uint32_t, uint32_t> get_curosr_position();

        /**
         * @brief Sets the cursor position
         *
         * @param pos The desired cursor position 
         */
        void set_cursor_position(std::pair<uint32_t, uint32_t> pos);

        /**
         * @brief Shows the cursor
         */
        void show_cursor();

        /**
         * @brief Hides the cursor
         */
        void hide_cursor();

        /**
         * @brief Resets terminal to original settings
         */
        void reset_terminal();

        [[deprecated]]
        void set_terminal_color(const Color& color);

        [[deprecated]]
        constexpr std::string color(const std::string_view text, const Color& color)  {
            return std::format("\033[38;2;{};{};{}m{}\033[0m", color.r, color.g, color.b, text); 
        }
    }
}
