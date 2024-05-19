#pragma once

#include <atomic>
#include <chrono>
#include <optional>
#include <thread>

namespace tuipp {
    inline namespace v0_0_1 {
        class Ticker final {
            private:
                std::chrono::microseconds interval;
                std::chrono::time_point<std::chrono::steady_clock> last_tick;
                std::atomic<bool> has_ticked{false};
                std::atomic<bool> stopped{false};
                std::thread thr;

                void loop() {
                    while(!stopped) {
                        while (has_ticked) {}
                        const auto now = std::chrono::steady_clock::now();
                        const auto now_diff = now - last_tick;
                        if (now_diff > interval) {
                            has_ticked = true;
                            last_tick = now;
                        }
                    }
                }

            public:
                Ticker() = delete;
                // TODO: Move semantics

                Ticker(std::chrono::microseconds intv): interval(intv), last_tick(std::chrono::steady_clock::now()) {}

                ~Ticker() {
                    if (!stopped) stop();
                }

                void start() {
                    thr = std::thread(&Ticker::loop, this);
                }

                void stop() {
                    stopped = true;
                    if (thr.joinable()) { thr.join(); }
                }

                auto C() {
                    while (!has_ticked) {}

                    auto ret = last_tick;
                    has_ticked = false;
                    return std::optional(ret);
                }
        };
    }
}
