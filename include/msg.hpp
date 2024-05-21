#pragma once

#include <key.hpp>

namespace tuipp {
    inline namespace v0_0_1 {
        struct Msg {
            virtual ~Msg() = default;
        };

        struct KeyMsg final: public Msg {
            Key Key;
            KeyMsg(struct Key Key): Key(Key) {}
        };

        struct QuitMsg final: public Msg {};
    }
}
