#include <rune.hpp>

namespace tuipp {
    inline namespace v0_0_1 {
        rune::rune(char c1, char c2, char c3, char c4) {
            *(reinterpret_cast<char*>(&codepoint)) = c1;
            *(reinterpret_cast<char*>(&codepoint) + 1) = c2;
            *(reinterpret_cast<char*>(&codepoint) + 2) = c3;
            *(reinterpret_cast<char*>(&codepoint) + 3) = c4;
        }

        rune::rune(std::string_view c) {
            if (c.size() <= 4) {
                char* codepoint_ptr = reinterpret_cast<char*>(&codepoint);
                codepoint_ptr[0] = c[0];
                codepoint_ptr[1] = c[1];
                codepoint_ptr[2] = c[2];
                codepoint_ptr[3] = c[3];
            }
        }

        rune::operator std::string() const {
            std::string ret = "";
            const char* codepoint_ptr = reinterpret_cast<const char*>(&codepoint);

            if (codepoint_ptr[0] != 0) ret += codepoint_ptr[0];
            if (codepoint_ptr[1] != 0) ret += codepoint_ptr[1];
            if (codepoint_ptr[2] != 0) ret += codepoint_ptr[2];
            if (codepoint_ptr[3] != 0) ret += codepoint_ptr[3];

            return ret;
        }

        bool rune::operator==(const rune& other) const {
            return codepoint == other.codepoint;
        }
    }
}
