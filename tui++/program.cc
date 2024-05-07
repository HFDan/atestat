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
        Program::~Program() { delete mod; }    

        std::pair<Model&, Program::err> Program::Start() {
            // Render the initial frame
            set_cursor_position(origin);
            DRAW_FRAME(mod);

            bool has_updated = false;
            while (!should_tuipp_quit) {
                KeyMsg* potentialKeyMessage = nullptr;
                if (kbhit()) {
                    if (!potentialKeyMessage) potentialKeyMessage = new KeyMsg;
                    potentialKeyMessage->Key=readKeyFromStdin();
                }

                if (potentialKeyMessage || has_updated) {                        
                    // Update
                    auto result = mod->Update(potentialKeyMessage);

                    has_updated = result.first;
                    auto cmd = result.second;
                    delete potentialKeyMessage;

                    // Render
                    set_cursor_position(origin);
                    DRAW_FRAME(mod);

                    if (cmd != nullptr) cmd();
                }
            }
            return {*mod, 0};
        }

        Program::Program(Model* mod): mod(mod) {
            ::printf("\033[0G"); // Move to start of line
            origin = get_curosr_position();
            
            mod->Init();
        }
    }
}
