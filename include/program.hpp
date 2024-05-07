#pragma once

#include <model.hpp>
#include <tuipp_base.hpp>

namespace tuipp {
    inline namespace v0_0_1 {
        class Program {
            private:
                Model* mod{nullptr};
                std::pair<uint32_t, uint32_t> origin{0, 0};

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

                void Send(/*msg*/) {};
                void SetWindowTitle(std::string_view title) {};
                void Wait() {};
                
            private:
                template <typename ModelType>
                friend Program NewProgram();

                Program(Model* mod);
        };

        template <typename ModelType>
        Program NewProgram() {
            init_base();
            auto* temp = new ModelType; 
            return Program(temp);
        };
    }
}
