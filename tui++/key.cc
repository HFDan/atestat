#include <key.hpp>

namespace tuipp {
    inline namespace v0_0_1 {
        Key::Key(KeyType Type, std::vector<rune>&& Runes, bool Alt): Type(Type), Runes(Runes), Alt(Alt) {

        }

        std::string Key::String() const {
            return static_cast<std::string>(*this);
        }

        Key::operator std::string() const {
            std::string ret;
            if (Type == KeyType::Rune) {
                for (auto rune : Runes)
                    ret += rune;

                return ret;
            }

            switch (Type) {
                case KeyType::Null:
                    ret = "null";
                    break;
                case KeyType::Enter:
                    ret = "enter";
                    break;
                case KeyType::Backspace:
                    ret = "backspace";
                    break;
                case KeyType::Esc:
                    ret = "esc";
                    break;
                case KeyType::CtrlA:
                    ret = "ctrl+a";
                    break;
                case KeyType::CtrlB:
                    ret = "ctrl+b";
                    break;
                case KeyType::CtrlC:
                    ret = "ctrl+c";
                    break;
                case KeyType::CtrlD:
                    ret = "ctrl+d";
                    break;
                case KeyType::CtrlE:
                    ret = "ctrl+e";
                    break;
                case KeyType::CtrlF:
                    ret = "ctrl+f";
                    break;
                case KeyType::CtrlG:
                    ret = "ctrl+g";
                    break;
                case KeyType::CtrlH:
                    ret = "ctrl+h";
                    break;
                case KeyType::CtrlI:
                    ret = "ctrl+i";
                    break;
                case KeyType::CtrlJ:
                    ret = "ctrl+d";
                    break;
                case KeyType::CtrlK:
                    ret = "ctrl+k";
                    break;
                case KeyType::CtrlL:
                    ret = "ctrl+l";
                    break;
                case KeyType::CtrlN:
                    ret = "ctrl+n";
                    break;
                case KeyType::CtrlO:
                    ret = "ctrl+o";
                    break;
                case KeyType::CtrlP:
                    ret = "ctrl+p";
                    break;
                case KeyType::CtrlQ:
                    ret = "ctrl+q";
                    break;
                case KeyType::CtrlR:
                    ret = "ctrl+r";
                    break;
                case KeyType::CtrlS:
                    ret = "ctrl+s";
                    break;
                case KeyType::CtrlT:
                    ret = "ctrl+t";
                    break;
                case KeyType::CtrlU:
                    ret = "ctrl+u";
                    break;
                case KeyType::CtrlV:
                    ret = "ctrl+v";
                    break;
                case KeyType::CtrlW:
                    ret = "ctrl+w";
                    break;
                case KeyType::CtrlX:
                    ret = "ctrl+x";
                    break;
                case KeyType::CtrlY:
                    ret = "ctrl+y";
                    break;
                case KeyType::CtrlZ:
                    ret = "ctrl+z";
                    break;
                case KeyType::CtrlBackslash:
                    ret = "ctrl+\\";
                    break;
                case KeyType::CtrlCloseBracket:
                    ret = "ctrl+]";
                    break;
                case KeyType::CtrlCaret:
                    ret = "ctrl+^";
                    break;
                case KeyType::CtrlUnderscore:
                    ret = "ctrl+_";
                    break;

                case KeyType::ArrowUp:
                    ret = "arrowup";
                    break;
                case KeyType::ArrowDown:
                    ret = "arrowdown";
                    break;
                case KeyType::ArrowLeft:
                    ret = "arrowleft";
                    break;
                case KeyType::ArrowRight:
                    ret = "arrowright";
                    break;

                default:
                    break;
            }

            return ret;
        }
    }
}
