#pragma once

#include <rune.hpp>

#include <cstdint>

#include <vector>
#include <string>

namespace tuipp {
    inline namespace v0_0_1 {
        enum class KeyType: int32_t {
            Rune = -1,

            Null = '\0',
            Break = 0x03,
            Enter = '\r',
            Backspace = 0x7f,
            Tab = '\t',
            Esc = 0x1b,
            Escape = 0x1b,

            CtrlAt = Null,
            CtrlA = 0x01,
            CtrlB = 0x02,
            CtrlC = 0x03,
            CtrlD = 0x04,
            CtrlE = 0x05,
            CtrlF = 0x06,
            CtrlG = '\a',
            CtrlH = '\b',
            CtrlI = '\t',
            CtrlJ = '\n',
            CtrlK = '\v',
            CtrlL = '\f',
            CtrlM = '\r',
            CtrlN = 0x0e,
            CtrlO = 0x0f,
            CtrlP = 0x10,
            CtrlQ = 0x11,
            CtrlR = 0x12,
            CtrlS = 0x13,
            CtrlT = 0x14,
            CtrlU = 0x15,
            CtrlV = 0x16,
            CtrlW = 0x17,
            CtrlX = 0x18,
            CtrlY = 0x19,
            CtrlZ = 0x1a,

            CtrlOpenBracket = Esc,
            CtrlBackslash = 0x1c,
            CtrlCloseBracket = 0x1d,
            CtrlCaret = 0x1e,
            CtrlUnderscore = 0x1f,
            CtrlQuestionmark = 0x7f,

            ArrowUp = Rune-1,
            ArrowDown = ArrowUp-1,
            ArrowLeft = ArrowDown-1,
            ArrowRight = ArrowLeft-1
        };

        /**
         * @class Key
         * @brief Stores a key representation, in runes and KeyTypes
         *
         */
        struct Key {
            KeyType Type{KeyType::Rune};
            std::vector<rune> Runes;
            bool Alt;

            Key() = default;
            Key(KeyType Type, std::vector<rune>&& Runes, bool Alt);

            /**
             * @brief Return the string representation of the key
             */
            std::string String() const;

            operator std::string() const;
        };
    }
}
