#pragma once

#include <functional>
#include <thread>

namespace tuipp {
    inline namespace v0_0_1 {
        typedef std::function<void(void)> Cmd;

        /**
         * @brief Runs multiple commands one after the other, guaranteed to be in order
         *
         * @param cmds The commands to run
         */
        template <typename... funcs>
        Cmd Sequence(funcs... cmds) {
            return [cmds...]() -> void {
                Cmd a[] = {cmds...};
                for (auto it : a)
                    it();
            };
        }

        /**
         * @brief Runs multiple commands simultaneously, makes no guarantees about order
         *
         * @param cmds The commands to run
         */
        template <typename... funcs>
        Cmd Batch(funcs... cmds) {
            return [cmds...]() -> void {
                const Cmd a[] = {cmds...};
                std::vector<std::jthread> threads;
                for (auto it : a)
                    threads.emplace_back(it);
            };
        }
    }
}
