#include <program.hpp>
#include <terminal.hpp>
#include <ticker.hpp>
#include <tuipp_base.hpp>

#define DRAW_FRAME(mod) \
::printf("\033[0J");\
fflush(stdout);\
::printf("%s", mod->View().c_str());\
fflush(stdout)\

namespace tuipp {
    inline namespace v0_0_1 {
        Program::~Program() { 
            delete mod;

            // We no longer need the mutex, since all threads *should* be done by the time the constructor is called
            while (!messageQueue.empty()) {
                auto* msg = messageQueue.front();
                delete msg;
                messageQueue.pop();
            }
        } 

        std::pair<Model&, Program::err> Program::Start() {
            // Render the initial frame
            set_cursor_position(origin);
            DRAW_FRAME(mod);

            bool has_updated = false;
            while (!should_tuipp_quit) {
                if (kbhit()) {
                    this->Send<tuipp::KeyMsg>(readKeyFromStdin());
                }

                while (!messageQueue.empty() || has_updated) {                        
                    tuipp::Msg* msg = nullptr;
                    if (!messageQueue.empty()){
                        std::lock_guard<std::mutex> lock(msgQueueMtx);
                        msg = messageQueue.front();
                        messageQueue.pop();
                    }

                    // Update
                    auto result = mod->Update(msg);
                    delete msg;

                    has_updated = result.first;
                    auto cmd = result.second;

                    // Render
                    set_cursor_position(origin);
                    DRAW_FRAME(mod);

                    // Run command
                    if (cmd != nullptr) cmd();
                }
            }
            return {*mod, 0};
        }

        Program::Program(Model* mod): mod(mod) {
            ::printf("\033[0G"); // Move to start of line
            origin = get_curosr_position();
            
            mod->prog = this;
            mod->Init();
        }
    }
}
