#pragma once
#include <terminal.hpp>
#include <key.hpp>

#include <termios.h>
#include <unistd.h>

namespace tuipp {
    inline namespace v0_0_1 {
        extern bool should_tuipp_quit;

        /**
         * @brief Instructs tuipp to quit
         */
        void Quit();

        void init_base();

        /**
         * @brief Reads a key from stdin
         *
         * @return tuipp::Key -> The read key
         */
        Key readKeyFromStdin();
    }
};
