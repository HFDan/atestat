#include <text.hpp>

#include <cstring>

namespace tuipp {
    inline namespace v0_0_1 {
        text::text() {
            
        }

        text::~text() {
            if (underlying_buffer) delete[] underlying_buffer;
        }

        rune& text::at(uint64_t idx) {
            return underlying_buffer[idx];
        }

        rune& text::operator[](uint64_t idx) {
            return underlying_buffer[idx];
        }

        rune* text::data() {
            return underlying_buffer;
        }

        void text::reserve(uint64_t count) {
            if (count <= capacity) return;

            rune* new_buf = new rune[count];
            std::memcpy(new_buf, underlying_buffer, length*sizeof(rune));
            delete[] underlying_buffer;
            underlying_buffer = new_buf;
        }

        void text::resize(uint64_t count) {

        }
    }
}
