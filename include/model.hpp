#pragma once

#include <msg.hpp>
#include <cmd.hpp>

#include <string>
#include <utility>

namespace tuipp {
    inline namespace v0_0_1 {
        struct Model {
            virtual ~Model() {}

            virtual std::string View() = 0;
            virtual void Init() = 0;
            [[nodiscard]] virtual std::pair<bool, Cmd> Update(const Msg* msg) = 0;
        };
    }
}
