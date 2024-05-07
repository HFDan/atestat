#pragma once
#include <rune.hpp>

#include <cstdint>

namespace tuipp {
    inline namespace v0_0_1 {
        class text {
            private:
                rune* underlying_buffer{nullptr};
                uint64_t length{0};
                uint64_t capacity{0};

            public:
                text();
                ~text();

                rune& at(uint64_t idx);
                rune& operator[](uint64_t idx);
                rune* data();
                bool empty();

                void reserve(uint64_t count);
                void resize(uint64_t count);
                // void resize(uint64_t count, rune r);
                
                void swap(text& other);
        };
    }
}
