#pragma once

#include <msg.hpp>
#include <cmd.hpp>

#include <program.hpp>
#include <string>
#include <utility>

namespace tuipp {
    inline namespace v0_0_1 {
        struct Model {
            Program* __Prog;
            virtual ~Model() {}

            virtual std::string View() = 0;
            virtual void Init() = 0;
            [[nodiscard]] virtual std::pair<bool, Cmd> Update(const Msg* msg) = 0;

            template<class MsgClass, typename... ConstructArgs>
            void Send(ConstructArgs... args) {
                return __Prog->Send<MsgClass>(args...);
            }
        };
    }
}
