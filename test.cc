#include <tuipp.hpp>

class TestMsg: public tuipp::Msg {
};

class Todo: public tuipp::Model {
    std::vector<std::pair<std::string, bool>> items;
    bool currently_adding = false;
    std::string addition;
    int cursor = 0;
    const std::string cursor_glyph = tuipp::Color::fromHex("#fb4934").toANSI() + ">" + tuipp::Color::ANSIdefault();

    virtual void Init() override { }
    virtual std::pair<bool, tuipp::Cmd> Update(const tuipp::Msg* msg) override {
        if (const auto* Test = dynamic_cast<const TestMsg*>(msg)) {
            items.emplace_back("! This is a test for the message queue !", true);
            return {true, nullptr};
        }
        if (const auto* KeyMsg = dynamic_cast<const tuipp::KeyMsg*>(msg)) {
            if (KeyMsg->Key.String() == "ctrl+c") { return {false, &tuipp::Quit};}

            if (currently_adding) {
                if (KeyMsg->Key.Type == tuipp::KeyType::Rune) {
                    addition += KeyMsg->Key.String();
                    return {true, nullptr};
                }
                if (KeyMsg->Key.Type == tuipp::KeyType::Backspace) {
                    addition = addition.substr(0, addition.size()-1);
                    return {true, nullptr};
                }
                if (KeyMsg->Key.Type == tuipp::KeyType::Enter) {
                    items.emplace_back(addition, false);
                    addition.clear();
                    currently_adding = false;
                    tuipp::hide_cursor();
                    return {true, nullptr};
                }
            } else {
                if (KeyMsg->Key.String() == "t") {
                    return {true, [this]() -> void {
                        prog->Send<TestMsg>();
                    }};
                    return {false, nullptr};
                }
                if (KeyMsg->Key.String() == "a") {
                    currently_adding = true;
                    tuipp::show_cursor();
                    return {true, nullptr};
                }
                if (KeyMsg->Key.Type == tuipp::KeyType::Enter) {
                    items[cursor].second = !items[cursor].second;
                    return {true, nullptr};
                }
                if (KeyMsg->Key.String() == "d") {
                    if (!items.empty() && cursor < items.size())
                        items.erase(items.begin()+cursor);
                    return {true, nullptr};
                }
                if (KeyMsg->Key.String() == "arrowup") {
                    if (cursor != 0)
                        cursor--;
                    else
                        cursor = items.size()-1;

                    return {true, nullptr};
                }
                if (KeyMsg->Key.String() == "arrowdown") {
                    if (cursor != items.size()-1)
                        cursor++;
                    else
                        cursor = 0;

                    return {true, nullptr};
                }
            }
        }

        return {false, nullptr};
    }

    virtual std::string View() override {
        std::string ret;
        ret = "Todo List\n\r";
        ret += tuipp::Color::fromHex("#a89984").toANSI() + "(Controls: [" +
            tuipp::Color::fromHex("#d3869b").toANSI() + "Enter" + tuipp::Color::fromHex("#a89984").toANSI() + "] - toggle complete; [" +
            tuipp::Color::fromHex("#d3869b").toANSI() + "d" + tuipp::Color::fromHex("#a89984").toANSI() + "] - delete; [" +
            tuipp::Color::fromHex("#d3869b").toANSI() + "t" + tuipp::Color::fromHex("#a89984").toANSI() + "] - send a test message to the application; [" +
            tuipp::Color::fromHex("#d3869b").toANSI() + "a" + tuipp::Color::fromHex("#a89984").toANSI() + "] - add)\n\r\n\r"
            + tuipp::Color::ANSIdefault();
        uint64_t i = 0;
        for (const auto&[item, completed] : items) {
            ret += std::format("{} [{}] {}\n\r", (i == cursor) ? cursor_glyph : " ", completed ? "*" : " ", item);
            i++;
        }
        ret += "\n\r";
        if (currently_adding) {
            ret += "\033[3m";
            ret += "\033[48;2;40;40;40m";
            ret += tuipp::Color::fromHex("#a89984").toANSI();
            ret += std::format("> {}", addition);
            ret += tuipp::Color::ANSIdefault();
        }

        return ret;
    }
};

int main(int argc, char** argv) {

    auto p = tuipp::NewProgram<Todo>();
    tuipp::hide_cursor();

    p.Start();

    return 0;
}
