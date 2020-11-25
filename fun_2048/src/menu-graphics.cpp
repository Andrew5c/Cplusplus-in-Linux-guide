#include "menu-graphics.hpp"
#include "global.hpp"
#include <sstream>


namespace Game
{
    namespace Graphics
    {
        namespace Menu
        {
            std::string mainMenuTitlePrompt() {
                constexpr auto greetings_text = "Welcome to ";
                constexpr auto gamename_text = "2048!";
                constexpr auto sp = "   ";

                std::ostringstream str_os;
                str_os << sp << greetings_text << gamename_text << "\n";
                return str_os.str();
            }

            // TODO：以后考虑增加“清除所有游戏记录”选项
            std::string mainMenuOptionsPrompt() {
                const auto menu_list_text = {"1. Play a new game",
                                             "2. Continue previous game",
                                             "3. View highscores",
                                             "4. Exit"};
                constexpr auto sp = "       ";

                std::ostringstream str_os;
                str_os << "\n";
                // TODO:这是什么语法?
                for(const auto text : menu_list_text) {
                    str_os << sp << text << "\n";
                }
                str_os << "\n";
                return str_os.str();
            }

            std::string inputMenuErrorPrompt() {
                constexpr auto input_error_text = "Invalid input. Please try again.";
                constexpr auto sp = "   ";

                std::ostringstream str_os;
                str_os << sp << input_error_text << "\n\n";
                return str_os.str();
            }

            std::string inputMenuPrompt() {
                constexpr auto choice_text = "Enter Choice: ";
                constexpr auto sp = "  ";

                std::ostringstream str_os;
                str_os << sp << choice_text;
                return str_os.str();
            }

            std::string mainMenuGraphicsOverlay(bool input_error) {
                std::ostringstream str_os;
                drawAlways(str_os, mainMenuTitlePrompt);
                drawAlways(str_os, mainMenuOptionsPrompt);
                drawOnlyWhen(str_os, input_error, inputMenuErrorPrompt);
                drawAlways(str_os, inputMenuPrompt);
                // return a string object
                return str_os.str();
            }
        } // namespace Menu
    } // namespace Graphics
} // namespace Game
