#pragma once

#include <key.hpp>

namespace tuipp {
    inline namespace v0_0_1 {
        struct Msg {
            virtual ~Msg() = default;
        };

        struct KeyMsg: public Msg {
            Key Key;
        };
    }
}
