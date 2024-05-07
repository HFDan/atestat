#include <rune.hpp>
#include <tuipp_base.hpp>

namespace tuipp {
    inline namespace v0_0_1 {
        bool should_tuipp_quit = false;

        void Quit() {
            should_tuipp_quit = true;
        }

        void init_base() {
            tcgetattr(STDIN_FILENO, &original_terminal_settings);
            raw_terminal();
            atexit(&reset_terminal);
        }

        
        Key readKeyFromStdin() {
            Key ret;
            char ascii_ch;
            read(STDIN_FILENO, &ascii_ch, 1);

            // We have an ascii key here
            if (!(ascii_ch & (1 << 7))) {
                // In this case, we have an ascii char
                if (ascii_ch >= 0x20 && ascii_ch <= 0x7e) {
                    ret.Runes.emplace_back(ascii_ch);
                    return ret;
                } else if (ascii_ch == '\033') {
                    // Skip the open bracket
                    char foo;
                    read(STDIN_FILENO, &foo, 1);

                    char arrowkey;
                    read(STDIN_FILENO, &arrowkey, 1);
                    switch (arrowkey) {
                        case 'A':
                            ret.Type = KeyType::ArrowUp;
                            break;
                        case 'B':
                            ret.Type = KeyType::ArrowDown;
                            break;
                        case 'C':
                            ret.Type = KeyType::ArrowRight;
                            break;
                        case 'D':
                            ret.Type = KeyType::ArrowLeft;
                            break;
                    }
                } else {
                    ret.Type = static_cast<KeyType>(ascii_ch);
                    return ret;
                }
            }
            
            // First utf-8 key
            {
                uint16_t codepoint_size = 1;
                bool keep_checking = true;
                if (ascii_ch & (1 << 6) && keep_checking) codepoint_size++; else keep_checking = false; 
                if (ascii_ch & (1 << 5) && keep_checking) codepoint_size++; else keep_checking = false; 
                if (ascii_ch & (1 << 4) && keep_checking) codepoint_size++; else keep_checking = false; 

                char rest_of_bytes[3] = {0};
                for (int i = 0; i < codepoint_size-1; i++) {
                    read(STDIN_FILENO, rest_of_bytes + i, 1);
                }

                ret.Runes.emplace_back(ascii_ch, rest_of_bytes[0], rest_of_bytes[1], rest_of_bytes[2]);
            }

            // If we have more chars available, keep going
            while (kbhit()) {
                char ch;

                // ch = getchar();
                read(STDIN_FILENO, &ch, 1);
                uint16_t codepoint_size = 0;
                bool keep_checking = true;
                if (ch & (1 << 7) && keep_checking) codepoint_size++; else keep_checking = false; 
                if (ch & (1 << 6) && keep_checking) codepoint_size++; else keep_checking = false; 
                if (ch & (1 << 5) && keep_checking) codepoint_size++; else keep_checking = false; 
                if (ch & (1 << 4) && keep_checking) codepoint_size++; else keep_checking = false; 

                char rest_of_bytes[3] = {0};
                for (int i = 0; i < codepoint_size-1; i++) {
                    // rest_of_bytes[i] = getchar(); 
                    read(STDIN_FILENO, rest_of_bytes + i, 1);
                }

                ret.Runes.emplace_back(ch, rest_of_bytes[0], rest_of_bytes[1], rest_of_bytes[2]);
            }
            return ret;
        }
    }
}
