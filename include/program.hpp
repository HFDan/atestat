#pragma once

#include <mutex>
#include <queue>

#include <msg.hpp>
#include <tuipp_base.hpp>

namespace tuipp {
    inline namespace v0_0_1 {
        class Model;
        class Program {
            private:
                Model* mod{nullptr};
                std::pair<uint32_t, uint32_t> origin{0, 0};

                std::queue<tuipp::Msg*> messageQueue;
                std::mutex msgQueueMtx;

            public:
                using err = uint64_t;

                ~Program();

                void Kill() {};
                void printf() {};
                void println() {};
                void Quit() {};
                void ReleaseTerminal() {};
                void RestoreTerminal() {};

                std::pair<Model&, err> Start();

                template<class MsgClass, typename... ConstructArgs>
                void Send(ConstructArgs... args) {
                    std::lock_guard<std::mutex> lock(msgQueueMtx);
                    messageQueue.push(new MsgClass(args...));
                };

                void SetWindowTitle(std::string_view title) {};
                void Wait() {};

            private:
                template <typename ModelType>
                friend Program NewProgram();

                Program(Model* mod);

                static bool isAlreadyInExistance;
        };

        template <typename ModelType>
        Program NewProgram() {
            if (!Program::isAlreadyInExistance) {
                init_base();
                auto* temp = new ModelType;
                return Program(temp);
            } else throw std::runtime_error("A program is already running. Tuipp does not support running multiple models at the same time.");
        };
    }
}
