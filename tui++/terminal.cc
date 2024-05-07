#include <terminal.hpp>
#include <color.hpp>

#include <cstdint>
#include <cstdio>

#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/ioctl.h>

namespace tuipp {
    inline namespace v0_0_1 {
        termios original_terminal_settings;

        bool kbhit() {
            int byteswaiting;
            ioctl(STDIN_FILENO, FIONREAD, &byteswaiting);
            return byteswaiting > 0;
        }

        void raw_terminal() {
            termios new_settings;

            tcgetattr(STDIN_FILENO, &new_settings);
            cfmakeraw(&new_settings);
            // new_settings.c_lflag |= ~(ECHO | ICANON);
            tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
        }

        std::pair<uint32_t, uint32_t> get_curosr_position() {
            printf("\033[6n");
            uint32_t row, col;
            scanf("\033[%u;%uR", &row, &col);
            return {row, col};
        }

        void set_cursor_position(std::pair<uint32_t, uint32_t> pos) {
            const auto& [row, col] = pos;
            printf("\033[%u,%uH", row, col);
        }

        void show_cursor() {
            printf("\033[?25h");
        }

        void hide_cursor() {
            printf("\033[?25l");
        }

        void reset_terminal() {
            tcsetattr(STDIN_FILENO, TCSANOW, &original_terminal_settings);
            show_cursor();
        }

        void set_terminal_color(const Color& color) {
            printf("\033[38;2;%u;%u;%um", color.r, color.g, color.b);
        }
    }
}
