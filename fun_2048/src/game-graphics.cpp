#include "game-graphics.hpp"
#include <sstream>
/*
1. 绘制游戏启动界面
*/

namespace Game
{
    namespace Graphics
    {
        std::string asciiArt2048() {
            // TODO: this give a good title card
            constexpr auto title_card_2048 = R"(2048)";
            std::ostringstream str_os;
            // TODO: add the color and fonts
            str_os << title_card_2048;
            str_os << "\n\n\n";
            // convert to string class
            return str_os.str();
        }

        std::string gameNoSavePrompt() {
            constexpr auto no_save_text = 
                "No saved game found. Starting a new game...";
            constexpr auto sp = "  ";
            std::ostringstream str_os;
            str_os << sp << no_save_text << "\n\n";
            return str_os.str();
        }
    } // namespace Graphics
    
} // namespace Game
