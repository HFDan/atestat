#pragma once
#include <cstdint>
#include <string>

namespace tuipp {
    inline namespace v0_0_1 {
#pragma pack(push, 1)
        /**
         * @class rune
         * @brief Stores a 32-bit utf-8 codepoint
         *
         */
        class rune final {
            static_assert(sizeof(uint32_t) == 4 * sizeof(char), "uint32_t cannot contain 4 chars, unable to compile on this platform");
            uint32_t codepoint{0};

            public: 
                rune() = default;

                rune(char c1, char c2 = 0, char c3 = 0, char c4 = 0);

                rune(std::string_view c);

                operator std::string() const;
                bool operator ==(const rune& other) const;

            //TODO: Move semantics
        };
#pragma pack(pop)
    }
}
